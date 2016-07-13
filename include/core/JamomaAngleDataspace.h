/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Angle Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2016 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/** Names of all units for the angle dataspace. 
		 */
		enum class AngleUnit : uint32_t {
			radian	= Hash("radian"),		///< radian (the neutral unit for this dataspace)
			rad		= Hash("rad"),			///< abbreviation for radian
			degree	= Hash("degree"),		///< degree
			deg		= Hash("deg")			///< abbreviation for degree
		};

		
		
		
		// Radian is the neutral unit, so it is a pass-through
		template <class T>
		class Radian : public UnitBase<T> {
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
		
		
		template <class T>
		class Degree : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input * kDegToRad;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * kRadToDeg;
			}
		};
		
		
		/**	The Angle Dataspace.
		 */
		template <class T,AngleUnit U>
		class Angle /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<AngleUnit, UnitBase<T>*>	sUnits = {
				{AngleUnit::radian, 	new Radian<T>()},
				{AngleUnit::rad, 		new Radian<T>()},
				{AngleUnit::degree, 	new Degree<T>()},
				{AngleUnit::deg, 		new Degree<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, const AngleUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T& x, uint32_t unit)
			{
				return (*this)(x, (AngleUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (AngleUnit)Hash(str) );
			}

		};
	
	} // namespace Dataspace
} // namespace Jamoma
