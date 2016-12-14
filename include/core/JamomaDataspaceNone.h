/** @file
	
	@ingroup 	jamoma2
	
	@brief 		None Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
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

			size_t dimensions() const {
				return 1;
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
			
			/// Query for the number of elements represented by the unit
			size_t dimensions() {
				return 1;
			}

			// TODO: should the above be T& references to make sure we don't copy anything?

		};
		
	
	} // namespace Dataspace
} // namespace Jamoma
