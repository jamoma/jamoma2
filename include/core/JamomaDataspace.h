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
#include "JamomaGainDataspace.h"
#include "JamomaNoneDataspace.h"
#include "JamomaTimeDataspace.h"


namespace Jamoma {
	
	// Convenience types for Parameter definitions
	namespace NativeUnit {
		
		// None
		template<typename T>
		using None			= Dataspace::None <T, Dataspace::NoneUnit::nothing>;
		
		// Angle
		using Radian		= Dataspace::Angle <double, Dataspace::AngleUnit::radian>;
		using Degree		= Dataspace::Angle <double, Dataspace::AngleUnit::degree>;
		
		// Gain
		using LinearGain	= Dataspace::Gain <double, Dataspace::GainUnit::linear>;
		using DbGain		= Dataspace::Gain <double, Dataspace::GainUnit::db>;
		using MidiGain		= Dataspace::Gain <double, Dataspace::GainUnit::midi>;
		
		// Time
		using Seconds		= Dataspace::Time <double, Dataspace::TimeUnit::seconds>;
		using Bark			= Dataspace::Time <double, Dataspace::TimeUnit::bark>;
		using Bpm			= Dataspace::Time <double, Dataspace::TimeUnit::bpm>;
		using Cents			= Dataspace::Time <double, Dataspace::TimeUnit::cents>;
		using Mel			= Dataspace::Time <double, Dataspace::TimeUnit::mel>;
		using MidiPitch		= Dataspace::Time <double, Dataspace::TimeUnit::midi>;
		using Milliseconds	= Dataspace::Time <double, Dataspace::TimeUnit::milliseconds>;
		using Fps			= Dataspace::Time <double, Dataspace::TimeUnit::fps>;
		using Hz			= Dataspace::Time <double, Dataspace::TimeUnit::hz>;
		using Samples		= Dataspace::Time <double, Dataspace::TimeUnit::samples>;
		using Speed			= Dataspace::Time <double, Dataspace::TimeUnit::speed>;
	}
	
	
	// Units for setting/getting parameters
	// TODO: it is not dry to duplicate all these -- but we need a common enum in order to have a shared interface for all Parameters
	enum class Unit : uint32_t {
		none			= (uint32_t)Dataspace::NoneUnit::nothing,
		
		radian			= (uint32_t)Dataspace::AngleUnit::radian,
		rad				= (uint32_t)Dataspace::AngleUnit::rad,
		degree			= (uint32_t)Dataspace::AngleUnit::degree,
		deg				= (uint32_t)Dataspace::AngleUnit::deg,
		
		linearGain		= (uint32_t)Dataspace::GainUnit::linear,
		db				= (uint32_t)Dataspace::GainUnit::db,
		midiGain		= (uint32_t)Dataspace::GainUnit::midi,
		
		seconds			= (uint32_t)Dataspace::TimeUnit::seconds,
		s				= (uint32_t)Dataspace::TimeUnit::s,
		bark			= (uint32_t)Dataspace::TimeUnit::bark,
		bpm				= (uint32_t)Dataspace::TimeUnit::bpm,
		cents			= (uint32_t)Dataspace::TimeUnit::cents,
		mel				= (uint32_t)Dataspace::TimeUnit::mel,
		midiPitch		= (uint32_t)Dataspace::TimeUnit::midi,
		milliseconds	= (uint32_t)Dataspace::TimeUnit::milliseconds,
		ms				= (uint32_t)Dataspace::TimeUnit::ms,
		fps				= (uint32_t)Dataspace::TimeUnit::fps,
		hertz			= (uint32_t)Dataspace::TimeUnit::hertz,
		hz				= (uint32_t)Dataspace::TimeUnit::hz,
		samples			= (uint32_t)Dataspace::TimeUnit::samples,
		speed			= (uint32_t)Dataspace::TimeUnit::speed
	};
	

} // namespace Jamoma

