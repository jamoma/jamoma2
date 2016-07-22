/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Temperature Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2016 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/** Names of all units for the temperature dataspace. 
		 */
		enum class TemperatureUnit : uint32_t {
			kelvin		= Hash("Kelvin"),		///< Kelvin (the neutral unit for this dataspace)
			k			= Hash("K"),			///< abbreviation for Kelvin
			celsius		= Hash("Celsius"),		///< Celsius
			c			= Hash("C"),			///< abbreviation for Celsius
			fahrenheit	= Hash("Fahrenheit"),	///< Fahrenheit
			f			= Hash("F")				///< abbreviation for Fahrenheit
		};
		
		
		
		
		// Kelvin is the neutral unit, so it is a pass-through
		template <class T>
		class Kelvin : public UnitBase<T> {
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
		class Celsius : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input + 273.15;
			}
			
			T fromNeutral(const T& input) const
			{
				return input - 273.15;
			}
		};
		
		
		template <class T>
		class Fahrenheit : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return (input + 459.67) / 1.8;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 1.8 - 459.67;
			}
		};
		
		
		/**	The Temperature Dataspace.
		 */
		template <class T,TemperatureUnit U>
		class Temperature /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<TemperatureUnit, UnitBase<T>*>	sUnits = {
				{TemperatureUnit::celsius, 		new Celsius<T>()},
				{TemperatureUnit::c, 			new Celsius<T>()},
				{TemperatureUnit::fahrenheit, 	new Fahrenheit<T>()},
				{TemperatureUnit::f, 			new Fahrenheit<T>()},
				{TemperatureUnit::kelvin, 		new Kelvin<T>()},
				{TemperatureUnit::k, 			new Kelvin<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, const TemperatureUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T& x, uint32_t unit)
			{
				return (*this)(x, (TemperatureUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (TemperatureUnit)Hash(str) );
			}

		};
	
	} // namespace Dataspace
} // namespace Jamoma
