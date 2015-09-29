/** @file
	
	@ingroup 	jamoma2
	
	@brief		Interfaces for passing values and collections of values.
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#pragma once


namespace Jamoma {
	
#pragma mark Tagged Values
	/**	A value together with some sort of marker such as a unit of measure, a label, etc.
		Typically this is used with a Unit from a Dataspace.
		
		For example `auto myVal = Tag(-6.0, Unit::Db);`
	 
		@see Tag()
	 */
	template <typename T>
	using TaggedValue = std::pair<T, Unit>;
	
	
	/**	Tag a value with some sort of marker such as a unit of measure, a label, etc.
		@param	a		The value
		@param	tag		The tag
		@return			A #TaggedValue containing both the value and the tag.
	 */
	template<typename T>
	constexpr
	auto Tag(T a, Unit tag) {
		return (TaggedValue<T>)std::make_pair(a, tag);
	}
	
	
	
	using Byte = char;
	

#pragma mark -
#pragma mark Var Base
	
	
	/*
		Values in Jamoma1 were essentially a wrapper for a std::vector of a tagged-union type.
		There are several changes to this for Jamoma2:
	 
		* We don't want to use std::vector if we don't have to -- it allocs on the heap instead of the stack.
		  In most cases we only have a single element in the value anyway.
		* Disambiguate between single values and vectors of values instead of always being forced 
		  to use the same vector even when you don't need/want that.
		* Create a value type that is extensible. 
		  In Jamoma1, to carry a new type in a value meant passing a void* and crossing your fingers.
		  Alternatively you could add a new type to the value itself by modifying the Foundation library.
		  Neither of these scenarios is good.
		  For example, extensions for the Nodelib should really be in the Nodelib code, not in the Foundation.
	 
		Having decided to split the "Value" and "Vector" into separate concerns, we can focus just on the Value.
	 
		The value could be implemented in a few different ways. 
		Primary among these is using a tagged union like in Jamoma1, but this has the problem of being non-extensible.
		The same is true of any "variant" types too (boost::variant, egg::variant, etc.) because they are discriminated unions.
		As a side-note, boost::any does it's allocation on the heap.
	 
		Of the aforementioned options, Eggs::Variant is particularly attractive as it is almost entirely constexpr!
		Ideally we could strive for the same in Jamoma::Value.
	 
		Thus our implementation in Jamoma2 (thus far) is to create base class to define the storage, 
		which is stack-allocated and has value semantics, but which is specialized by subclasses/templates.
	 
		The downside (compared to eggs::variant) is that since we use virtual functions we cannot make it
		constexpr.
	
		An interesting approach that might be able to be made constexpr is discussed at
		http://www.drdobbs.com/an-efficient-variant-type/184402027
		It basically relies on virtual functions but it does so by creating it's own vtable manually.
	 
	 
	 
		And now having defined a Value, and then defining a Vector to be vector of Values, 
		we need a unified way of passing Values and Vectors.
		This is a new type, which we'll call a Var.
		The Var should be (as far as possible) constexpr so that there is no wrangling to figure the types at runtime.
		The Var could be a variant type, or perhaps something simpler -- maybe even a union if that works in C++11.
	 
	 
	 
		Or perhaps a Value can contain a Vector?
		In this case we should rename to Var to avoid ambiguity and to make it easier to talk about,
		as opposed big-V Value and little-v value.
	 
		We certainly want it to be able to contain a Pair for values with units.
	 
	 
	 */
	
	
	/*
		TODO: universal references for perfect forwarding...
	 */
	
	
	
	
	
	
//#define VARIANT_BASED_VALUE
#ifdef VARIANT_BASED_VALUE
	
	
	
// how to make a template class...
//	template <>
//	class variant<>
//	{

	/*

		This implementation is uses Egg.Variant ( https://github.com/eggs-cpp/variant ) which internally is a discriminated union.
		The downside to this implementation is that all types that are going to be used by the union must be declared in advance.
		The upside is that all instances of the Value use C++ value semantics and are created/destroyed on the stack.
		Specific to the Eggs.Variant implementation is that much of this is a constexpr and calls can be executed at compile time.
	 
		@see http://stackoverflow.com/questions/18856824/ad-hoc-polymorphism-and-heterogeneous-containers-with-value-semantics
		@see http://boost.2283326.n4.nabble.com/Another-variant-type-was-peer-review-queue-tardiness-was-Cleaning-out-the-Boost-review-queue-Review--td4674046.html
		@see http://talesofcpp.fusionfenix.com/post-20/eggs.variant---part-ii-the-constexpr-experience
	 */
	
	using namespace eggs;


	using Value		= eggs::variant<int, double, Function>;
	using Vector	= std::vector<Value>;
	using Var		= eggs::variant<Value, Vector>;
	
	
	// Actually, a vector won't work in a variant -- maybe a shared_ptr to a vector would?  sigh...
	// One of the explicit limitations of a variant is that it doesn't support types with heap-allocated memory.
	
	
	
	

	//	template<>
//	class Value : public eggs::variant<int, double, Function> {
	

	
	template <typename ...Ts>
	class Variant : public eggs::variant<Ts...> {
	public:
		// TODO: is there a downside to accessing values like this?
		// It seems strange it would not have been implemented in eggs already?
		template<typename U>
		constexpr operator U() const {
//			U temp;
//			variants::get<U>(temp);
//			return temp;
			return variants::get<U>(*this);
		}
		
		
		constexpr Variant() noexcept
		{}
		
/*
		template<typename U>
		Variant(U arg)
		: eggs::variant<Ts...>(arg)
		{}
*/
		
		
		/**	Assignment operator.
			@param	value	The value from which to assign.
		 Type conversions will be done prior to assignment.
		 */
//		template<typename U>
//		Variant& operator = (const U& rhs) {
//			return eggs::variant<Ts...>::operator=(rhs);
//		}

		
		template<typename U>
		constexpr Variant& operator = (U rhs) {
			return eggs::variant<Ts...>::operator=(rhs);
		}

	
	};
	
	
	
	// this is how we typically pass values around generically in Jamoma
	// vector's storage is on the heap, so it's fine to include here without ballooning the mem footprint
//	using Var = eggs::variant<Value, Vector>;
/*	template<>
	class Var : public eggs::variant<Value, Vector> {
		
		// TODO: is there a downside to accessing values like this?
		// It seems strange it would not have been implemented in eggs already?
		template<typename U>
		operator U() const {
			U temp;
			variants::get<U>(temp);
			return temp;
		}
		
	};
*/	// TODO: the above is duplicated -- so maybe it should be one class...  a Jamoma::Variant
	
	
#else
	
	
	
	template <class T> class Var; // forward declaration
	
	
	/** The Value class provides a way to represent an arbitrary type of value.
		A limited amount of memory is allocated on the stack for storage of the value.
		Specializations of more extravagant types my alloc memory on the heap and store it here if needed.
	 
		This implementation uses a generic ValueBase class with templated specialization for specific data types and conversions.
		It is important that the Value<> specializations do *not* have any additional member variables, as they will be stripped when copying/moving through ValueBase instances
	 */
	class VarBase {
		template <class T> friend class Var;
		
		/**	The size of the memory allocated for a Var on the stack.
			This size will support std::pair<double>, std::vector, std::chrono time types, etc.
			This is not large enough for std::function, which thus requires it's own specialization.
		 */
		constexpr static size_t sSize = 24;
		
		static_assert(sSize >= sizeof(std::vector<double>),		"Var is large enough to hold std::vector");
		static_assert(sSize >= sizeof(TaggedValue<double>),		"Var is large enough to hold TaggedValue<double>");
		static_assert(sSize >= sizeof(TimePoint),				"Var is large enough to hold TimePoint");
		static_assert(sSize >= sizeof(std::array<double, 3>),	"Var is large enough to hold std::array<double, 3>");
		static_assert(sSize >= sizeof(std::string),				"Var is large enough to hold std::string");
		
		/**	Type of the data represented by the Var. */
//		const std::type_info* mType = {&typeid(nullptr)};
		const std::type_info& mType = {typeid(nullptr)};
		
		
		/**	Storage for the type. */
//		Byte mData[sSize] = {};
// TODO: should change to std::array to get bounds catching etc.
		std::array<Byte, sSize>		mData = {};
		
		
	public:
		/**	Create a Value with an initial value.
			@param initial	The initial value for the Value. The type of the Value will be taken from the initial value's type.
		 */
		template <typename U>
		VarBase(const U initial)
		: mType { typeid(U) }
//		: mType { &typeid(U) }
		{
			Var<U>* specialization = (Var<U>*)(this);
			*specialization = initial;
		}
	

		VarBase(const std::type_info& aType)
		: mType { aType }
		{}

		
		/** Default constructor with no specialization. 
			Intended for internal use only.
		 */
		VarBase()
		{}
		
		
		/**	Destroy a Value.
		 */
		virtual ~VarBase()
		{}
		
		
		/**	Assign a value to an Value.
			TODO: If the specialization changes then we may have resources to release!
			@param	value	The value to be assigned.
			@discussion		The actual implementation of the assignment is performed by the specialized Value, not by the ValueBase itself.
		 */
		template<typename U>
		VarBase& operator = (const U value)
		{
			Var<U>* specialization = dynamic_cast<Var<U>*>(this);
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
			assert(typeid(U) == mType);
//			static_assert( std::is_same<U, mType>::value , "Can only cast from Var to the native type.");
			const Var<U>* specialization = (const Var<U>*)this;
			return *specialization;
		}
	};
	
	
	/**	Value specialization for most basic types of data.
		This specialization assumes that the data is a stored directly on the stack and the type is not some sort of pointer or reference.
		TODO: can we use some type deduction to perform some compile-time assertions?
	 */
	template <class T>
	class Var : public VarBase {
	public:
		/** Create an uninitialized Value.
			Initializing the value at construction is strongly preferred.
		 */
		Var()
		: VarBase(typeid(T))
		{}
		
		/** Create an initialized Value.
			@param	initial	The value with which to initialize.
		 */
		Var(T initial)
		{
			*this = initial;
		}
		
		
		// because we have value semantics we can use the default copy/move constructors and assignments
		// however, we might need to set the type by calling the base class ctor ???
		Var(const Var&) = default;
		Var(Var&&) = default;
		// TODO: copy assign and move assign
		
		
		/**	Assignment operator from another Value.
			@param	value	The value from which to assign.
		 */
		Var& operator = (const VarBase& value)
		{
			mData = value.mData;
			return *this;
		}
		
		
		/**	Assignment operator.
			@param	value	The value from which to assign. 
							Type conversions will be done prior to assignment.
		 */
		Var& operator = (const T& value)
		{
//			memcpy(mData, *(char**)&value, sizeof(char)*8);
			//			mData = value.mData;
			T* data = (T*)&mData[0];
			
			*data = value;
			return *this;
		}
		
		
		/**	Casting operator to fetch the value.
			@return	The value.
		 */
		operator T() const
		{
			T* data = (T*)&mData[0];
			T		value = *data;
//			memcpy(*(char**)&value, mData, sizeof(char)*8);
			return value;
		}
	};
	
#endif

} // namespace Jamoma
