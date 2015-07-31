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
	
	/** A hash function using the Murmur3 algorithm. */
	constexpr inline uint32_t Hash(const char *const str, const uint32_t seed = 0xAED123FD) noexcept
	{
		return Murmur3_32(str, _StringLength(str), seed);
	}

	
	
	using Synopsis = const char*;

	template <typename T>
	using Boundaries = std::pair<T, T>;
	
	enum class BoundaryBehavior {
		none,
		clip,
		wrap,
		fold
	};
	

		// change name to range (was boundaries) because an enum range can be listed in the future potentially
	enum class RangeLimit : uint32_t {
		none = Hash("none"),
		clip = Hash("clip"),
		wrap = Hash("wrap"),
		fold = Hash("fold")
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
