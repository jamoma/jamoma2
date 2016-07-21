/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Shared Dataspace Structures
	
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {
	namespace Dataspace {
	
		
		/** Base class for all "Units" defined for a Dataspace. */
		template <class T>
		class UnitBase {
		public:
			virtual T toNeutral(const T& input) const = 0;
			virtual T fromNeutral(const T& input) const = 0;
		};
		
		
	} // namespace Dataspace
} // namespace Jamoma


#include "JamomaAngleDataspace.h"
#include "JamomaDistanceDataspace.h"
#include "JamomaGainDataspace.h"
#include "JamomaNoneDataspace.h"
#include "JamomaSpeedDataspace.h"
#include "JamomaTemperatureDataspace.h"
#include "JamomaTimeDataspace.h"


namespace Jamoma {
	
	// Convenience types for Parameter definitions
	namespace NativeUnit {
		
		// None
		template<typename T>
		using None				= Dataspace::None <T, Dataspace::NoneUnit::nothing>;
		
		// Angle
		using Radian			= Dataspace::Angle <double, Dataspace::AngleUnit::radian>;
		using Degree			= Dataspace::Angle <double, Dataspace::AngleUnit::degree>;
		
		// Distance
		using Meters			= Dataspace::Distance <double, Dataspace::DistanceUnit::meters>;
		using Centimeters		= Dataspace::Distance <double, Dataspace::DistanceUnit::centimeters>;
		using Feet				= Dataspace::Distance <double, Dataspace::DistanceUnit::feet>;
		using Inches			= Dataspace::Distance <double, Dataspace::DistanceUnit::inches>;
		
		// Gain
		using LinearGain		= Dataspace::Gain <double, Dataspace::GainUnit::linear>;
		using DbGain			= Dataspace::Gain <double, Dataspace::GainUnit::db>;
		using MidiGain			= Dataspace::Gain <double, Dataspace::GainUnit::midigain>;
		
		// Speed
		using MeterPerSecond	= Dataspace::Speed <double, Dataspace::SpeedUnit::meterPerSecond>;
		using KilometerPerHour	= Dataspace::Speed <double, Dataspace::SpeedUnit::kilometerPerHour>;
		using Kmph				= Dataspace::Speed <double, Dataspace::SpeedUnit::kmph>;
		using MilesPerHour		= Dataspace::Speed <double, Dataspace::SpeedUnit::milesPerHour>;
		using Mphr				= Dataspace::Speed <double, Dataspace::SpeedUnit::mphr>;
		using FootPerSecond		= Dataspace::Speed <double, Dataspace::SpeedUnit::footPerSecond>;
		using Knot				= Dataspace::Speed <double, Dataspace::SpeedUnit::knot>;
				
		// Temperature
		using Celsius			= Dataspace::Temperature <double, Dataspace::TemperatureUnit::celsius>;
		using C					= Dataspace::Temperature <double, Dataspace::TemperatureUnit::c>;
		using Fahrenheit		= Dataspace::Temperature <double, Dataspace::TemperatureUnit::fahrenheit>;
		using F					= Dataspace::Temperature <double, Dataspace::TemperatureUnit::f>;
		using Kelvin			= Dataspace::Temperature <double, Dataspace::TemperatureUnit::kelvin>;
		using K					= Dataspace::Temperature <double, Dataspace::TemperatureUnit::k>;
		
		// Time
		using Seconds			= Dataspace::Time <double, Dataspace::TimeUnit::seconds>;
		using Bark				= Dataspace::Time <double, Dataspace::TimeUnit::bark>;
		using Bpm				= Dataspace::Time <double, Dataspace::TimeUnit::bpm>;
		using Cents				= Dataspace::Time <double, Dataspace::TimeUnit::cents>;
		using Mel				= Dataspace::Time <double, Dataspace::TimeUnit::mel>;
		using MidiPitch			= Dataspace::Time <double, Dataspace::TimeUnit::midi>;
		using Milliseconds		= Dataspace::Time <double, Dataspace::TimeUnit::milliseconds>;
		using Fps				= Dataspace::Time <double, Dataspace::TimeUnit::fps>;
		using Hz				= Dataspace::Time <double, Dataspace::TimeUnit::hz>;
		using Samples			= Dataspace::Time <double, Dataspace::TimeUnit::samples>;
		using PlayBackSpeed		= Dataspace::Time <double, Dataspace::TimeUnit::playbackspeed>;
	}
	
	
	// Units for setting/getting parameters
	// TODO: it is not dry to duplicate all these -- but we need a common enum in order to have a shared interface for all Parameters
	enum class Unit : uint32_t {
		none				= (uint32_t)Dataspace::NoneUnit::nothing,
		
		radian				= (uint32_t)Dataspace::AngleUnit::radian,
		rad					= (uint32_t)Dataspace::AngleUnit::rad,
		degree				= (uint32_t)Dataspace::AngleUnit::degree,
		deg					= (uint32_t)Dataspace::AngleUnit::deg,
		
		meters				= (uint32_t)Dataspace::DistanceUnit::meters,
		m					= (uint32_t)Dataspace::DistanceUnit::m,
		cemtimeters			= (uint32_t)Dataspace::DistanceUnit::centimeters,
		cm					= (uint32_t)Dataspace::DistanceUnit::cm,
		feet				= (uint32_t)Dataspace::DistanceUnit::feet,
		feetSign			= (uint32_t)Dataspace::DistanceUnit::feetSign,
		inchesSign			= (uint32_t)Dataspace::DistanceUnit::inchesSign,
		
		linearGain			= (uint32_t)Dataspace::GainUnit::linear,
		db					= (uint32_t)Dataspace::GainUnit::db,
		midiGain			= (uint32_t)Dataspace::GainUnit::midigain,
		
		meterPerSecond		= (uint32_t)Dataspace::SpeedUnit::meterPerSecond,
		kilometerPerHour	= (uint32_t)Dataspace::SpeedUnit::kilometerPerHour,
		kmph				= (uint32_t)Dataspace::SpeedUnit::kmph,
		milesPerHour		= (uint32_t)Dataspace::SpeedUnit::milesPerHour,
		mphr				= (uint32_t)Dataspace::SpeedUnit::mphr,
		footPerSecond		= (uint32_t)Dataspace::SpeedUnit::footPerSecond,
		knot				= (uint32_t)Dataspace::SpeedUnit::knot,
		
		c					= (uint32_t)Dataspace::TemperatureUnit::c,
		celsius				= (uint32_t)Dataspace::TemperatureUnit::celsius,
		f					= (uint32_t)Dataspace::TemperatureUnit::f,
		fahrenheit			= (uint32_t)Dataspace::TemperatureUnit::fahrenheit,
		k					= (uint32_t)Dataspace::TemperatureUnit::k,
		kelvin				= (uint32_t)Dataspace::TemperatureUnit::kelvin,
			
		seconds				= (uint32_t)Dataspace::TimeUnit::seconds,
		s					= (uint32_t)Dataspace::TimeUnit::s,
		bark				= (uint32_t)Dataspace::TimeUnit::bark,
		bpm					= (uint32_t)Dataspace::TimeUnit::bpm,
		cents				= (uint32_t)Dataspace::TimeUnit::cents,
		mel					= (uint32_t)Dataspace::TimeUnit::mel,
		midiPitch			= (uint32_t)Dataspace::TimeUnit::midi,
		milliseconds		= (uint32_t)Dataspace::TimeUnit::milliseconds,
		ms					= (uint32_t)Dataspace::TimeUnit::ms,
		fps					= (uint32_t)Dataspace::TimeUnit::fps,
		hertz				= (uint32_t)Dataspace::TimeUnit::hertz,
		hz					= (uint32_t)Dataspace::TimeUnit::hz,
		samples				= (uint32_t)Dataspace::TimeUnit::samples,
		speed				= (uint32_t)Dataspace::TimeUnit::playbackspeed
	};
	

} // namespace Jamoma

