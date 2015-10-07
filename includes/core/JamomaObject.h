/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Create Jamoma Object instances.
	
	@details 	Parent class for all Objects within the Jamoma library. 
				Defines common features such as Parameters and Messages that are used by all Objects throughout the codebase.
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

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

#include "JamomaDataspace.h"


namespace Jamoma {
	

		
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
	

	class ParameterBase; // forward-declartion needed by Object
	
	
	/**	The base class for all first-class objects in Jamoma.
		Such classes maybe used with traditional C++ compile-time linking or addressed dynamically my sending messages.
	 */
	class Object {
		template <class T, class U, RangeLimit> friend class Parameter;
		
		// we really just care that we have a pointer, not about the type of the attribute
		// attributes can be raw pointers because they are only accessed and owned by our class
		// TODO: perhaps these should still be done using STL "smart raw" pointers?
		// TODO: index should be the return type of the Hash function instead of a String? -- then we would lose all of the names...
		using ParameterMap = std::unordered_map<String, ParameterBase*>;
		
		// Internal: a mapping of parameter names to the parameters themselves.
		ParameterMap	parameters;

	public:
		/** Theoretically: constructor for users of an object that is created by dynamic lookup, e.g. 
			@code
			Jamoma::Object filter("lowpass.4");
			@endcode
		 
			TODO: implement
		 */
		Object(String name)
		{}
		

		/**	Inherited constructor for users of an object that is created statically/directly
			@code
			Jamoma::LowpassFourpole	my_filter;
			@endcode
		 */
		Object()
		{}
		
	
		// TODO: do we also need a constexpr constructor so that objects can register and add their tags? how does that all work?
	
		
		/** Destructor. */
		virtual ~Object()
		{}
		
		
		/** send a message to the object dynamically
		 */
		VarBase send(const String& name, const VarBase& input)
		{
			return 0;	// TODO: stub
		}
		
		/** send a message to the object dynamically 
		 */
		VarBase send(const String& name)
		{
			return 0;	// TODO: stub
		}
	};


} // namespace Jamoma
