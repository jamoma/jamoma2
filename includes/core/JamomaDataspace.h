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


#include "JamomaGainDataspace.h"
#include "JamomaNoneDataspace.h"


namespace Jamoma {
	
	// Convenience types for Parameter definitions
	namespace NativeUnit {
		
		// None
		template<typename T>
		using None			= Dataspace::None <T, Dataspace::NoneUnit::nothing>;
		
		// Gain
		using LinearGain	= Dataspace::Gain <double, Dataspace::GainUnit::linear>;
		using DbGain		= Dataspace::Gain <double, Dataspace::GainUnit::db>;
		using MidiGain		= Dataspace::Gain <double, Dataspace::GainUnit::midi>;
	}
	
	
	// Units for setting/getting parameters
	// TODO: it is not dry to duplicate all these -- but we need a common enum in order to have a shared interface for all Parameters
	enum class Unit : uint32_t {
		none		= (uint32_t)Dataspace::NoneUnit::nothing,
		
		linearGain	= (uint32_t)Dataspace::GainUnit::linear,
		db			= (uint32_t)Dataspace::GainUnit::db,
		midiGain	= (uint32_t)Dataspace::GainUnit::midi
	};
	

} // namespace Jamoma

