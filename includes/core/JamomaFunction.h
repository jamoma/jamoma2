/** @file
	
	@ingroup jamoma2
	
	@brief	Function class and related hooks.
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once


namespace Jamoma {
	

	/**	A function.	*/
	using Function = std::function<void(void)>;

	
	
	/**	Value specialization for the Function type
	 */
	template <>
	class Var<Function> : public VarBase {
	public:
		
		auto data() const noexcept {
			return (Function**)&mData[0];
		}
		
		/** Create an uninitialized Function Value.
			Initializing the value at construction is preferred.
		 */
		Var()
		: VarBase(typeid(Function))
		{
//			Function* data = (Function*)&mData[0];
			*data() = new Function; // can't use placement new because we don't have enough memory
		}
		
		
		/** Create a Value initialized with a Function.
			@param	initial		The Function with which to initialize.
		 */
		Var(Function initial)
		: VarBase(typeid(Function))
		{
//			Var<Function>::Var();
//			Function** data = (Function**)&mData[0];
			*data() = new Function; // can't use placement new because we don't have enough memory
			*this = initial;
		}
		
		
		/** Copy constructor */
		Var(const Var& other)
		: VarBase(typeid(Function))
		{
//			Var<Function>::Var();
//			Function* data = (Function*)&mData[0];
			*data() = new Function; // can't use placement new because we don't have enough memory
			
			Function f = other;
			*this = f;
		}
		
		
		// TODO: Move ctor

		
		/** Destructor */
		virtual ~Var()
		{
//			Function* data = (Function*)&mData[0];
			delete *data();
		}
		
		
		/**	Assignment operator.
			@param	value	The Function to be assigned.
		 */
		Var& operator = (const Function& value)
		{
//			Function* data = (Function*)&mData[0];
			**data() = value;
			return *this;
		}
		
		
		/**	Casting operator to fetch the Function.
			@return	The Function.
		 */
		operator Function() const noexcept
		{
//			Function* data = (Function*)&mData[0];

			return **data();
		}
	};


} // namespace Jamoma
