/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Time Dataspace
	
	@author 	Trond Lossius, Timothy Place, Nils Peters
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaDataspace.h"


namespace Jamoma {
	namespace Dataspace {
			
	
		/** Names of all units for the time dataspace.
		 */
		enum class TimeUnit : uint32_t {
			seconds			= Hash("second"),			///< seconds (the neutral unit for this dataspace)
			s				= Hash("s"),				///< seconds
			bark			= Hash("bark"),				///< bark band number ( https://en.wikipedia.org/wiki/Bark_scale )
			bpm				= Hash("bpm"),				///< beats per minute
			cents			= Hash("cents"),			///< cents (pitch)
			mel				= Hash("mel"),				///< mel scale ( https://en.wikipedia.org/wiki/Mel_scale )
			midinote		= Hash("midinote"),			///< midi pitch number (0-127)
			milliseconds	= Hash("millisecond"),		///< milliseconds
			ms				= Hash("ms"),				///< milliseconds
			fps				= Hash("fps"),				///< frames per second
			hertz			= Hash("hertz"),			///< hertz -- cycles per second
			hz				= Hash("hz"),				///< hertz
			samples			= Hash("samples"),			///< samples (dependent upon sample rate)
			// We can't use "speed" as it leads to a naming conflict with the Speed Dataspace.
			playbackspeed	= Hash("playbackspeed"),	///< speed -- e.g. playback speed relative to 1.0
		};

		
		
		
		// Linear is the neutral unit, so it is a pass-through
		template <class T>
		class Seconds : public UnitBase<T> {
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
		class Bark : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				// code from http://labrosa.ee.columbia.edu/matlab/rastamat/bark2hz.m
				return 1.0 / (600 * sinh(double(input) / 6));
			}
			
			T fromNeutral(const T& input) const
			{
				// taken from http://labrosa.ee.columbia.edu/matlab/rastamat/hz2bark.m
				return (6 * asinh(1.0 / (double(input) * 600.0)));
			}
		};
		
		
		template <class T>
		class Bpm : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				//TODO: prevent division with zero
				return 60.0 / double(input);
			}
			
			T fromNeutral(const T& input) const
			{
				//TODO: prevent division with zero
				return 60.0 / double(input);
			}
		};
		
		
		template <class T>
		class Cents : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return 1.0 / (440.0 * pow(2.0, (double(input)-6900.0) / 1200.0 ));
			}
			
			T fromNeutral(const T& input) const
			{
				return 6900.0 + 1200.0 * log(1.0/(440.0*double(input)))/log(2.0);
			}
		};
		
		
		template <class T>
		class Hz : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				//TODO: prevent division with zero
				return 1.0 / double(input);
			}
			
			T fromNeutral(const T& input) const
			{
				//TODO: prevent division with zero
				return 1.0 / double(input);
			}
		};
		
		
		template <class T>
		class Mel : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				// HTK-code from http://labrosa.ee.columbia.edu/matlab/rastamat/mel2hz.m
				return 1.0 / (700.0 *(pow(10,(double(input)/2595.0))-1.0));
			}
			
			T fromNeutral(const T& input) const
			{
				// HTK-code from http://labrosa.ee.columbia.edu/matlab/rastamat/hz2mel.m
				return 2595.0 * log10(1+1.0/(double(input)*700.0));
			}
		};
		
		
		template <class T>
		class MidiNote : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return 1. / (440.0 * pow(2.0, (double(input)-69.0) / 12.0 ));
			}
			
			T fromNeutral(const T& input) const
			{
				// return 69.0 + 12.0 * log(1./(440.0*TTFloat64(input)))/log(2.0);
				// The above can be transformed to the slightly more optimised:
				return 69.0 - 12.0 * log(440.0*double(input))/log(2.0);
			}
		};
		
		
		template <class T>
		class Milliseconds : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				return input * 0.001;
			}
			
			T fromNeutral(const T& input) const
			{
				return input * 1000.0;
			}
		};
		
		
		template <class T>
		class Samples : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				assert(false); // Need to get global sample rate
				double sampleRate = 96000;
				return (input) / sampleRate;
			}
			
			T fromNeutral(const T& input) const
			{
				assert(false); // Need to get global sample rate
				double sampleRate = 96000;
				return (input) * sampleRate;
			}
		};
		
		
		template <class T>
		class PlayBackSpeed : public UnitBase<T> {
		public:
			T toNeutral(const T& input) const
			{
				// Here's one way of converting:
				//
				// TTFloat64 midi;
				// 1) speed => midi
				//		midi = 12.0 * log(TTFloat64(input))/log(2.0);
				// 2) midi => second
				//		output = 1. / (440.0 * pow(2.0, (midi-69.0) / 12.0 ));
    
				// This is an optimized version of the above:
				return pow(2.0, 69./12.) / (440.0*double(input));
			}
			
			T fromNeutral(const T& input) const
			{
				// Here's one way of converting from second to speed:
				//
				// TTFloat64 midi;
				// 1) second => midi
				//		midi = 69.0 - 12.0 * log(440.0*TTFloat64(input))/log(2.0);
				// 2) midi => speed
				//		output = pow(2.0, (midi/12.0));
	
				// Optimized in a similar way to the above:
				return pow(2.0, 69./12.) / (440.0*double(input));
			}
		};
		
		
		/**	The Time Dataspace.
		 */
		template <class T, TimeUnit U>
		class Time {
			
			/**	Mapping from unit names to actual unit converter objects.
				TODO: make this a static so that we don't have to spend resources on it for all instances
			 */
			std::unordered_map<TimeUnit, UnitBase<T>*>	sUnits = {
				{TimeUnit::seconds			, new Seconds<T>()},
				{TimeUnit::s				, new Seconds<T>()},
				{TimeUnit::bark				, new Bark<T>()},
				{TimeUnit::bpm				, new Bpm<T>()},
				{TimeUnit::cents			, new Cents<T>()},
				{TimeUnit::mel				, new Mel<T>()},
				{TimeUnit::midinote			, new MidiNote<T>()},
				{TimeUnit::milliseconds		, new Milliseconds<T>()},
				{TimeUnit::ms				, new Milliseconds<T>()},
				{TimeUnit::fps				, new Hz<T>()},
				{TimeUnit::hertz			, new Hz<T>()},
				{TimeUnit::hz				, new Hz<T>()},
				{TimeUnit::samples			, new Samples<T>()},
				{TimeUnit::playbackspeed    , new PlayBackSpeed<T>()}
			};

			
			/**	The native unit to/from which we perform conversions.	*/
			const UnitBase<T>* mUnit = sUnits[U];

			
		public:
			
			/**	Conversion function where the unit is passed as enum selection.	*/
			T operator()(const T& x, const TimeUnit& unit = U)
			{
				return mUnit->fromNeutral( sUnits[unit]->toNeutral(x) );
			}

			T operator()(const T& x, uint32_t& unit)
			{
				return (*this)(x, (TimeUnit)unit);
			}
		
			/**	Conversion function where the unit is passed as a string.	*/
			T operator()(const T x, const char* str)
			{
				return (*this)( x, (TimeUnit)Hash(str) );
			}

		};
	
	} // namespace Dataspace
} // namespace Jamoma
