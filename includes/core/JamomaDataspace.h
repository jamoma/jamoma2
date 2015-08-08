/** @file
	
	@ingroup jamoma2
	
	@brief Shared Dataspace Structures
	
	@author Tim Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once


namespace Jamoma {
	namespace Dataspace {
	
		
		/** Base class for all "Units" defined for a Dataspace. */
		template <class T>
		class Unit {
		public:
			virtual T toNeutral(const T input) const = 0;
			virtual T fromNeutral(const T input) const = 0;
		};
		
	
	} // namespace Dataspace
} // namespace Jamoma
