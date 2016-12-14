/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Speed Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2016 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/** Names of all units for the speed dataspace. 
		 */		
		enum class SpeedUnit : uint32_t {
			meterPerSecond		= Hash("m/s"),		///< meter per second (the neutral unit for this dataspace)
			kilometerPerHour	= Hash("km/s"),		///< kilometers per hour
			kmph				= Hash("kmph"),		///< alternative notation for kilometers per hour
			milesPerHour		= Hash("mi/h"),		///< miles per hour
			mphr				= Hash("mph"),		///< alternative notation for miles per hour
			footPerSecond		= Hash("ft/s"),		///< foot per second
			knot				= Hash("kn")		///< knot
		};
		
		
		
		
		// meter per second is the neutral unit, so it is a pass-through
		template <class T>
		class MeterPerSecond : public UnitBase<T> {
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
		
		
		template <class T>
		class KilometerPerHour : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input / 3.6;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 3.6;
			}

			size_t dimensions() const {
				return 1;
			}
		};
		
		
		template <class T>
		class MilesPerHour : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input * 0.44704;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 2.236936;
			}

			size_t dimensions() const {
				return 1;
			}
		};
		
		
		template <class T>
		class FootPerSecond : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input * 0.3048;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 3.2808399;
			}

			size_t dimensions() const {
				return 1;
			}
		};
		
		
		template <class T>
		class Knot : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input * 0.514444;	//not exact
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 1.943844;	//not exact
			}

			size_t dimensions() const {
				return 1;
			}
		};
		
		
		/**	The Speed Dataspace.
		 */
		template <class T,SpeedUnit U>
		class Speed /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			
			std::unordered_map<SpeedUnit, UnitBase<T>*>	sUnits = {
				{SpeedUnit::meterPerSecond, 		new MeterPerSecond<T>()},
				{SpeedUnit::kilometerPerHour, 		new KilometerPerHour<T>()},
				{SpeedUnit::kmph, 					new KilometerPerHour<T>()},
				{SpeedUnit::milesPerHour, 			new MilesPerHour<T>()},
				{SpeedUnit::mphr, 					new MilesPerHour<T>()},
				{SpeedUnit::footPerSecond, 			new FootPerSecond<T>()},
				{SpeedUnit::knot, 					new Knot<T>()},
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, const SpeedUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T& x, uint32_t unit)
			{
				return (*this)(x, (SpeedUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (SpeedUnit)Hash(str) );
			}

			/// Query for the number of elements represented by the unit
			size_t dimensions() {
				return mUnit->dimensions();
			}
		};
	
	} // namespace Dataspace
} // namespace Jamoma
