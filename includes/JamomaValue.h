
#pragma once

#include <string>
#include <typeinfo>
#include <cassert>
#include <array>

namespace Jamoma {
	
	template <class T> class Value;
	
	/** The Value class provides a way to represent an arbitrary type of value.
		A limited amount of memory is allocated on the stack for storage of the value.
		Specializations of more extravagant types my alloc memory on the heap and store it here if needed.
	 
		This implementation uses a generic ValueBase class with templated specialization for specific data types and conversions.
		It is important that the Value<> specializations do *not* have any additional member variables, as they will be stripped when copying/moving through ValueBase instances
	 */
	class ValueBase {
		template <class T> friend class Value;
		
		
		/**	The type of the data represented by the Value.
		 */
		const std::type_info* mType = {&typeid(nullptr)};
		
		
		/**	The data, or a pointer to the data if a specialization uses it in that way.
		 */
		char mData[8] = {0,0,0,0,0,0,0,0};
		
		
	public:
		/**	Create a Value with an initial value.
			@param initial	The initial value for the Value. The type of the Value will be taken from the initial value's type.
		 */
		template <typename U>
		ValueBase(const U initial)
		: mType { &typeid(U) }
		{
			Value<U>* specialization = (Value<U>*)(this);
			*specialization = initial;
		}
		
		
		ValueBase()
		{}
		
		
		/**	Destroy a Value.
		 */
		virtual ~ValueBase()
		{}
		
		
		/**	Assign a value to an Value.
			TODO: If the specialization changes then we may have resources to release!
			@param	value	The value to be assigned.
			@discussion		The actual implementation of the assignment is performed by the specialized Value, not by the ValueBase itself.
		 */
		template<typename U>
		ValueBase& operator = (const U value)
		{
			Value<U>* specialization = dynamic_cast<Value<U>*>(this);
			*specialization = value;
			return *this;
		}
		
		
		/**	Fetch the Value.
			The requested type *must* match the type of the Value.
			@return			The Value
			@discussion		The actual implementation of the assignment is performed by the specialized Value, not by the ValueBase itself.
		 */
		template<typename U>
		operator U() const
		{
			assert(typeid(U) == *mType);
			const Value<U>* specialization = (const Value<U>*)this;
			return *specialization;
		}
	};
	
	
	/**	Value specialization for most basic types of data.
	 */
	template <class T>
	class Value : public ValueBase {
	public:
		Value()
		{
			mType = &typeid(T);
		}
		
		
		Value(T initial)
		{
			*this = initial;
		}
		
		
		Value& operator = (const ValueBase& value)
		{
			mType = &typeid(T);
			mData = value.mData; // TODO: but if it's a pointer we need a copy, use a shared_pointer, or ???
			return *this;
		}
		
		
		Value& operator = (const T value)
		{
			mType = &typeid(T);
			memcpy(mData, *(char**)&value, sizeof(char)*8);
			return *this;
		}
		
		
		operator T() const
		{
			T value;
			memcpy(*(char**)&value, mData, sizeof(char)*8);
			return value;
		}
	};
	
	
	/**	Value specialization for the Function type
	 */
	template <>
	class Value<Function> : public ValueBase {
	public:
		Value()
		{
			mType = &typeid(Function);
			memcpy(mData, *(char**) new Function, sizeof(char)*8);
		}
		
		
		Value(Function initial)
		{
			mType = &typeid(Function);
			memcpy(mData, *(char**) new Function, sizeof(char)*8);
			*this = initial;
		}
		
		
		virtual ~Value()
		{
			delete (Function*)mData;
		}
		
		
		Value& operator = (const Function value)
		{
			mType = &typeid(Function);
			*(Function*)mData = value;
			return *this;
		}
		
		
		operator Function() const
		{
			return *(Function*)mData;
		}
	};

}
