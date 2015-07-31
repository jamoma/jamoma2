/** @file
	
	@ingroup jamoma2
	
	@brief Create Jamoma Object instances.
	
	@details Parent class for all Objects within the Jamoma library. 
	Defines common features such as Parameters and Messages that are used by all Objects throughout the codebase.
	
	@author Timothy Place, Nathan Wolek
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>
#include <array>


#include "Murmur3.h" // used for constexpr hash function



namespace Jamoma {
	
	/** A hash function using the Murmur3 algorithm ( https://en.wikipedia.org/wiki/MurmurHash ).
		This hash function is capable of being executed at compile time,
		meaning that the compiled binary will have a constant int value and no actually need to execute any code at runtime.
		@param	str		A c-string to be hashed into an int.
		@param	seed	An optional seed value.  For most uses you should not override the default.
		@return			An int (specifically a uint32_t) representing the hash of the string input.
	 */
	constexpr inline uint32_t Hash(const char *const str, const uint32_t seed = 0xAED123FD) noexcept
	{
		return Murmur3_32(str, _StringLength(str), seed);
	}

		
	/**	Defines the bounds of a Parameter.
		The low-bound comes first, then the high-bound.
	 */
	template <typename T>
	using Range = std::pair<T, T>;
	

	/** The behavior of a Parameter when the suggested Range is exceeded. */
	enum class RangeLimit : uint32_t {
		none = Hash("none"),			///< Don't do anything.
		clip = Hash("clip"),			///< Limit to the min and max values defined by the Range.
		wrap = Hash("wrap"),			///< Wrap back around to the low/high value if the Range is exceeded.
		fold = Hash("fold")				///< Mirror the value back down into the defined Range.
	};
	

	class ParameterBase;
	
	class Object {
		template <class T, RangeLimit> friend class Parameter;
		
		// we really just care that we have a pointer, not about the type of the attribute
		// attributes can be raw pointers because they are only accessed and owned by our class
		using ParameterMap = std::unordered_map<String, ParameterBase*>;
		
		ParameterMap	parameters;

	public:
		// constructor for users of an object that is created by dynamic lookup, e.g. Jamoma::Object filter("lowpass.4");
		Object(String name)
		{}
		
		// constructor for users of an object that is created statically/directly
		Object()
		{}
		
		// do we also need a constexpr constructor ?
		// that way objects can register and add their tags?
		// how does that all work?
		
		virtual ~Object()
		{}
		
		
		/** send a message to the object dynamically
		 */
		ValueBase send(const String& name, const ValueBase& input)
		{
			return Value<int>(0);	// TODO: stub
		}
		
		/** send a message to the object dynamically 
		 */
		ValueBase send(const String& name)
		{
			return Value<int>(0);	// TODO: stub
		}
	};


} // namespace Jamoma
