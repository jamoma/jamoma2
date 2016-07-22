/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Gain Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
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
			linear = Hash("linear"),		///< linear gain (the neutral unit for this dataspace)
			midigain = Hash("midigain"),	///< midi gain where 100 is unity
			db = Hash("db")					///< decibels
		};

		
		
		
		// Linear is the neutral unit, so it is a pass-through, although it is required to be >= 0.
		template <class T>
		class LinearGain : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return std::max(input, 0.0);
			}
			
			T fromNeutral(const T& input) const
			{
				return input;
			}
		};
		
		
		template <class T>
		class MidiGain : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				// Range-check incling MIDI value
				if (input > 0.) {
					// Convert MIDI to dB
					T temp = 96* ( pow( (input/100.), (pow(2, kGainMidiPower))) - 1);
					// Convert dB to linear, we know that range is safe
					return(pow(10., (temp * 0.05)));
				}
				else
					return 0.0;
			}
			
			T fromNeutral(const T& input) const
			{
				// Convert linear to dB
				T temp = 20.0 * (log10(input));
				// Range-check dB and convert to MIDI
				if (temp <= -96.)
					return 0.;
				else
					return 100 * exp((log(temp/96. + 1.))/kGainMidiPowPow2);
			}
		};
		
		
		template <class T>
		class DbGain : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				if (input > -96.)
					return pow(10.0, input * 0.05);
				else
					return 0.0;
			}
			
			T fromNeutral(const T& input) const
			{
				return std::max(log10(input) * 20.0, -96.);
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
		
			Cases where there are specific performance concerns we can further specialize the templates.
		 */
		template <class T, GainUnit U>
		class Gain /*: public Dataspace*/ {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<GainUnit, UnitBase<T>*>	sUnits = {
				{GainUnit::linear,		new LinearGain<T>()},
				{GainUnit::midigain,	new MidiGain<T>()},
				{GainUnit::db,			new DbGain<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, const GainUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T& x, uint32_t unit)
			{
				return (*this)(x, (GainUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (GainUnit)Hash(str) );
			}

		};
	
	} // namespace Dataspace
} // namespace Jamoma
