/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Define a parameter of a JamomaObject
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaObject.h"

namespace Jamoma {
	
	
	/** ParameterBase allows us a unified means for referencing a Parameter of any template-specialization.
		All Parameters must be defined using a Parameter<type> specialization and this base class is for internal use only.
	 */
	class ParameterBase {
	protected:
		Object*					mOwner;				///< The owning Jamoma::Object to which this Parameter belongs.
		String					mName;				///< The name of this Parameter as it would be addressed dynamically.
		Synopsis				mSynopsis = "";		///< A description of what this Parameter represents.
		Setter					mSetter = nullptr;	///< A function to be executed after the parameter's value has been set.
		std::vector<Observer*>	mObservers;			///< Objects receiving notifications when this parameter has been set.

		// TODO: the above raw pointer will lead to dangling references ?!?!?!?!

		ParameterBase(Object* owner, const String& name )
		: mOwner(owner)
		, mName(name)
		{}
		
		
		virtual ~ParameterBase()
		{}
		
	public:
		String& name()
		{
			return mName;
		}
		
		friend bool operator == (const ParameterBase& lhs, const char* rhs)
		{
			return lhs.mName == rhs;
		}
		
		virtual ParameterBase& operator = (const VarBase& input) = 0;
		
		
		void addObserver(Observer& anObserver)
		{
			mObservers.push_back(&anObserver);
		}
		
		
		void removeObserver(Observer& anObserver)
		{
			// documentation of the below: https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), &anObserver), mObservers.end());
		}
		
	};
	
	
	/**	Define a parameter of a Jamoma::Object.
		@tparam	T				The C++ data type of the Parameter (e.g. int, double, Jamoma::Sample, etc.)
	 	@tparam	LimitType		(optional) The name of a class defining behavior applied to received values that are out of Range (e.g. Jamoma::Limit::Clip<double>).
		@tparam	DataspaceType	(optional) The name of a class defining a dataspace unit for the parameter so that values received in alternate units may be converted correctly.
	 */
	template <	class T,
				class LimitType = Limit::None<T>,
				class DataspaceType = Dataspace::None<T, Dataspace::NoneUnit::nothing>
			 >
	class Parameter : public ParameterBase {
	public:
		
		Parameter() = delete;		// constructor: can't create an unitialized Parameter

		
	private:
		/** constructor utility: handle an argument defining a parameter's synopsis	
		 */
		template <typename U>
		typename std::enable_if<std::is_same<U, Synopsis>::value>::type assignFromArgument(const U& arg) {
			mSynopsis = arg;
		}
		
		/** constructor utility: handle an argument defining a parameter's range	
		 */
		template <typename U>
		typename std::enable_if<std::is_same<U, Range<T>>::value>::type assignFromArgument(const U& arg) {
			mRange = arg;
		}
		
		/** constructor utility: handle an argument defining a parameter's setter function	
		 */
		template <typename U>
		typename std::enable_if<std::is_same<U, Setter>::value>::type assignFromArgument(const U& arg) {
			mSetter = arg;
		}
		
		/** constructor utility: empty argument handling (required for recursive variadic templates)	
		 */
		void handleArguments() {
			;
		}
		
		/** constructor utility: handle N arguments of any type by recursively working through them 
			and matching them to the type-matched routine above. 
		 */
		template <typename FIRST_ARG, typename ...REMAINING_ARGS>
		void handleArguments(FIRST_ARG const& first, REMAINING_ARGS const& ...args) {
			assignFromArgument(first);
			if (sizeof...(args))
				handleArguments(args...);		// recurse
		}
		
		
	public:
		/** constructor
			@param	owner	A pointer to the object instance to whom the parameter belongs (pass `this` from your class)
			@param	name	A string specifying the name of the parmeter when dynamically addressed or inspected
			@param	initial	Initial value for the parameter
			@param	...args	N arguments specifying optional properties of a parameter such as Setter, Range, Synopsis, etc.
		 */
		template <typename...ARGS>
		Parameter(Object* owner, String name, T initial, ARGS...args)
		: ParameterBase(owner, name)
		, mValue(initial)
		{
			handleArguments(args...);
		}
		
		
		/**	Set the value of the parameter	
		 */
		Parameter& operator = (T input) {
			set(input);
			return *this;
		}
		
		
		/**	Set the value of the parameter using the specified unit, which will be converted automatically if needed.	
		 */
		Parameter& operator = (const std::pair<T, Unit> input) {
			set(input.first, input.second);
			return *this;
		}
		
		
		/**	Set the value of the parameter from a generic Var 
		 */
		// TODO: if a Var has 2 members then do we use the last one as a unit? perhaps it needs some metadata so that we know?
		Parameter& operator = (const VarBase& input) {
			set(input);
			return *this;
		}
		
		
		/**	Set the *value* of the parameter from another Parameter
		 */
		Parameter& operator = (const Parameter& input) {
			set(input.mValue);
			return *this;
		}
		
		
		/**	Get the value of the Parameter
		 */
		operator T() const {
			return this->mValue;
		}


	private:
		
		/** worker fn for setters: naked values have no dataspace unit specified, so set them directly
		 */
		void set(T input) {
			this->mValue = LimitType::apply(input, this->mRange.first, this->mRange.second);
			if (this->mSetter)
				this->mSetter();
			for (auto& observer : this->mObservers)
				(*observer)();
		}
		

		/** worker fn for setters: set values using a dataspace conversion
		 */
		void set(T input, Unit unit) {
			set(mDataspace(input, (uint32_t)unit));
		}
		
		
		T					mValue;		///< the actual value storage
		Range<T>			mRange;		///< range of the parameter
		DataspaceType		mDataspace;	///< dataspace of the parameter
	};
	
} // namespace Jamoma
