/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Distance Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2016 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/** Names of all units for the distance dataspace. 
		 */
		enum class DistanceUnit : uint32_t {
			meters		= Hash("meters"),			///< meters (the neutral unit for this dataspace)
			m			= Hash("m"),				///< abbreviation for meters
			centimeters	= Hash("centimeters"),		///< centimeters
			cm			= Hash("cm"),				///< abbreviation for centimeters
			inches		= Hash("inches"),			///< inches
			inchesSign	= Hash("\""),				///< abbreviation for inches
			feet		= Hash("feet"),				///< feet
			feetSign	= Hash("'")					///< abbreviation for feet
		};

		
		
		
		// METER is the neutral unit, so it is a pass-through
		template <class T>
		class Meters : public UnitBase<T> {
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
		class Centimeters : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input * 0.01;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 100.0;
			}
		};
		
		
		template <class T>
		class Inches : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input / 39.37;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 39.37;
			}
		};
		
		
		
		template <class T>
		class Feet : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input / 3.2808399;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 3.2808399;
			}
		};
		
		
		/**	The Distance Dataspace.
		 */
		template <class T,DistanceUnit U>
		class Distance /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<DistanceUnit, UnitBase<T>*>	sUnits = {
				{DistanceUnit::meters, 			new Meters<T>()},
				{DistanceUnit::m,	 			new Meters<T>()},
				{DistanceUnit::centimeters, 	new Centimeters<T>()},
				{DistanceUnit::cm, 				new Centimeters<T>()},
				{DistanceUnit::feet,			new Feet<T>()},
				{DistanceUnit::feetSign,		new Feet<T>()},
				{DistanceUnit::inches,			new Inches<T>()},
				{DistanceUnit::inchesSign,		new Inches<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, const DistanceUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T& x, uint32_t unit)
			{
				return (*this)(x, (DistanceUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (DistanceUnit)Hash(str) );
			}

		};
	
	} // namespace Dataspace
} // namespace Jamoma
