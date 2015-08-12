/** @file
	
	@ingroup jamoma2
	
	@brief Gain Dataspace
	
	@author Trond Lossius, Tim Place, Nils Peters
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/** Names of all units for this dataspace.
		 */
		enum class NoneUnit : uint32_t {
			nothing = Hash("nothing"),	///< do nothing (the neutral unit for this dataspace)
		};

		
		// the neutral unit is always a pass-through
		// compiler inlining should make it a noop
		template <class T>
		class Nothing : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input;
			}
			
			T fromNeutral(const T& input) const
			{
				return input;
			}
		};
		
		
		/**	The "None" Dataspace -- no dataspace at all.
			
			NOTE: needs to be a template because we don't want to alter data by going through doubles if it isn't a double
		 */
		template <class T, NoneUnit U>
		class None /*: public Dataspace*/ {
		public:
			
			T operator()(const T& x)
			{
				return x;
			}
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, NoneUnit& unit)
			{
				return x;
			}

			
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T& x, const char* str)
			{
				return x;
			}
			
			// TODO: should the above be T& references to make sure we don't copy anything?

		};
		
	
	} // namespace Dataspace
} // namespace Jamoma
