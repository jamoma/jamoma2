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
			
	
		/** Names of all units for the gain dataspace. 
			Implementation Note: This must be specified outside of the Gain dataspace class 
			so that it can be used to specialize the templates for the Gain dataspace class.
		 */
		enum class GainUnit : uint32_t {
			linear = Hash("linear"),	///< linear gain (the neutral unit for this dataspace)
			midi = Hash("midi"),		///< midi gain where 100 is unity
			db = Hash("db")				///< decibels
		};

		
		
		
		// Linear is the neutral unit, so it is a pass-through
		template <class T>
		class LinearGain : public UnitBase<T> {
		public:
			T toNeutral(const T input) const
			{
				return input;
			}
			
			T fromNeutral(const T input) const
			{
				return input;
			}
		};
		
		
		template <class T>
		class MidiGain : public UnitBase<T> {
		public:
			T toNeutral(const T input) const
			{
				return pow(input*0.01, kTTGainMidiPower);
			}
			
			T fromNeutral(const T input) const
			{
				return 100.0 * pow(input, kTTGainMidiPowerInv);
			}
		};
		
		
		template <class T>
		class DbGain : public UnitBase<T> {
		public:
			T toNeutral(const T input) const
			{
				return pow(10.0, input * 0.05);
			}
			
			T fromNeutral(const T input) const
			{
				T temp = log10(input) * 20.0;
				
				// Output decibel range is limited to 24 bit range, avoids problems with singularities (-inf) when using dataspace in ramps
				if (temp < -144.49)
					temp = -144.49;
				return temp;
			}
		};
		
		
		/**	The Gain Dataspace.
		 
			In Jamoma1 you would create a Gain Dataspace object and then it would do all possible conversions as you.
			In Jamoma2 we create an instance that is specialized for the "native" unit that you want to convert to/from.
		 
			You then pass values to the instance along with a tag the specifies the unit.
			
			In Jamoma1 the unit was maintained as part of the state of the dataspace instance.
			In Jamoma2 the dataspace instance is stateless and you must specify the unit tag every time.
		 
			Lots of problems stem from trying to be stateful -- remembering what the unit is when new 'naked' values come in
			is not always accurate when values might come pouring in from different sources simultaneously (rampers, mappers, etc).
			
			In all cases, even with specifying the unit every time, 
			the performance of the new implementation should exceed that of the Jamoma1 implementation.
			TODO: perform actual benchmarks and publish the results.
		
			Cases where there are specific performance concerns we can further specialize the templates to offer
			superior and branch-free conversions.
		 */
		template <class T, GainUnit U>
		class Gain /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<GainUnit, UnitBase<T>*>	sUnits = {
				{GainUnit::linear, new LinearGain<T>()},
				{GainUnit::midi, new MidiGain<T>()},
				{GainUnit::db, new DbGain<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T x, GainUnit unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T x, uint32_t unit)
			{
				return (*this)(x, (GainUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (GainUnit)Hash(str) );
			}

		};
		
		
		/*
		// specialization for linear gain because it is so common and we would like to optimize for this case
		template <class T>
		class Gain<T, GainUnit::linear> {
			
		public:
			
			static std::unordered_map<const uint32_t, Unit<T>>	sUnits2 = {
				{GainUnit::linear, LinearGain<T>()},
				{GainUnit::midi, MidiGain<T>()},
				{GainUnit::db, DbGain<T>()}
			};
			
			
			T operator()(const T x, GainUnit unit = GainUnit::linear)
			{
				return sUnits2[unit].toNeutral(x);
			}
			
		};

		*/
		
	
	} // namespace Dataspace
} // namespace Jamoma
