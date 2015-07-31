/** @file
	
	@ingroup jamoma2
	
	@brief Define a parameter of a JamomaObject
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaObject.h"

namespace Jamoma {
	
	
	// Allows us a unified means for referencing a Parameter of any template-specialization
	// The bool part is only present as a type of some sort is required -- this trick learned from std::string implementation
	//template <bool>
	//class ParameterBase {
	class ParameterBase {
		Object*				mOwner;
		String				mName;
		
	public:
		ParameterBase(Object* owner, const String& name)
		: mOwner(owner)
		, mName(name)
		{}
		
		virtual ~ParameterBase()
		{}
		
		String& name()
		{
			return mName;
		}
		
		friend bool operator == (const ParameterBase& lhs, const char* rhs)
		{
			return lhs.mName == rhs;
		}
		
		virtual ParameterBase& operator = (const ValueBase& input) = 0;
		
	};
	
	template <class T, RangeLimit rangeLimit = RangeLimit::none>
	// class Parameter : public ParameterBase<true> {
	class Parameter : public ParameterBase {
		T					mValue;
		Synopsis			mSynopsis;
		Range<T>			mRange;
		RangeLimit			mRangeLimit;
		Function			mSetter = { nullptr };
		// getter
		
	public:
		
		// Can't create an unitialized Parameter
		// TODO: need to do this for specializations of Value too?
		Parameter() = delete;
		
		//template <typename F>
		//Parameter(Object* owner, String name, T initial, ...)
		Parameter(Object* owner, String name, T initial)
		: ParameterBase(owner, name)
		, mValue(initial)
		, mRangeLimit(RangeLimit::none)
		{
			// 1. iterate args
			// 2. determine their types
			// 3. do something appropriate for their given type
			// 4. can we make this whole thing constexpr ?
			
			// need to have a default-setter closure, and default-getter closure to use if none are passed-in
			
			owner->parameters[name] = this;
			if (mSetter)
				mSetter();
		}
		
		
		Parameter(Object* owner, String name, T initial, Function setter)
		: ParameterBase(owner, name)
		, mValue(initial)
		, mRangeLimit(RangeLimit::none)
		, mSetter(setter)
		{
			// 1. iterate args
			// 2. determine their types
			// 3. do something appropriate for their given type
			// 4. can we make this whole thing constexpr ?
			
			// need to have a default-setter closure, and default-getter closure to use if none are passed-in
			
			owner->parameters[name] = this;
			if (mSetter)
				mSetter();
		}
		
		
		// setter
		Parameter& operator = (T input)
		{
			mValue = input;
			if (mSetter)
				mSetter();
			return *this;
		}
		
		
		// setter for case when input is a generic value
		Parameter& operator = (const ValueBase& input)
		{
			mValue = (T)input;
			if (mSetter)
				mSetter();
			return *this;
		}
		
		
		// assign *values* from one attribute to another
		Parameter& operator = (Parameter& input)
		{
			mValue = input.mvalue;
			if (mSetter)
				mSetter();
			return *this;
		}
		
		
		// getter
		operator T() const
		{
			return mValue;
		}
	};
	
	
	// Parameters that clip
	//		template <class T, RangeLimit::clip>
	template<class T>
	class Parameter<T, RangeLimit::clip> : public ParameterBase {
		T					mValue;
		Synopsis			mSynopsis;
		Range<T>			mRange;
		RangeLimit			mRangeLimit;
		Function			mSetter = { nullptr };
		// getter
		
	public:
		
		// Can't create an unitialized Parameter
		// TODO: need to do this for specializations of Value too?
		Parameter() = delete;
		
		//template <typename F>
		//Parameter(Object* owner, String name, T initial, ...)
		Parameter(Object* owner, String name, T initial)
		: ParameterBase(owner, name)
		, mValue(initial)
		, mRangeLimit(RangeLimit::clip)
		{
			// 1. iterate args
			// 2. determine their types
			// 3. do something appropriate for their given type
			// 4. can we make this whole thing constexpr ?
			
			// need to have a default-setter closure, and default-getter closure to use if none are passed-in
			
			owner->parameters[name] = this;
			if (mSetter)
				mSetter();
		}
		
		
		Parameter(Object* owner, String name, T initial, Function setter)
		: ParameterBase(owner, name)
		, mValue(initial)
		, mRangeLimit(RangeLimit::clip)
		, mSetter(setter)
		{
			// 1. iterate args
			// 2. determine their types
			// 3. do something appropriate for their given type
			// 4. can we make this whole thing constexpr ?
			
			// need to have a default-setter closure, and default-getter closure to use if none are passed-in
			
			owner->parameters[name] = this;
			if (mSetter)
				mSetter();
		}

		Parameter(Object* owner, String name, T initial, Range<T> range, Function setter)
		: ParameterBase(owner, name)
		, mValue(initial)
		, mRange(range)
		, mRangeLimit(RangeLimit::clip)
		, mSetter(setter)
		{
			// 1. iterate args
			// 2. determine their types
			// 3. do something appropriate for their given type
			// 4. can we make this whole thing constexpr ?
			
			// need to have a default-setter closure, and default-getter closure to use if none are passed-in
			
			owner->parameters[name] = this;
			if (mSetter)
				mSetter();
		}

		
		// setter
		Parameter& operator = (T input)
		{
			mValue = Limit(input, mRange.first, mRange.second);
			if (mSetter)
				mSetter();
			return *this;
		}
		
		
		// setter for case when input is a generic value
		Parameter& operator = (const ValueBase& input)
		{
			mValue = (T)input;
			if (mSetter)
				mSetter();
			return *this;
		}
		
		
		// assign *values* from one attribute to another
		Parameter& operator = (Parameter& input)
		{
			mValue = input.mvalue;
			return *this;
		}
		
		
		// getter
		operator T() const
		{
			return mValue;
		}
	};


} // namespace Jamoma
