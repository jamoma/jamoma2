/** @file
	
	@ingroup jamoma2
	
	@brief Shared Dataspace Structures
	
	@author Tim Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once


namespace Jamoma {
	namespace Dataspace {
	
		
		/** Base class for all "Units" defined for a Dataspace. */
		template <class T>
		class UnitBase {
		public:
			virtual T toNeutral(const T input) const = 0;
			virtual T fromNeutral(const T input) const = 0;
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
		None		= (uint32_t)Dataspace::NoneUnit::nothing,
		
		LinearGain	= (uint32_t)Dataspace::GainUnit::linear,
		Db			= (uint32_t)Dataspace::GainUnit::db,
		MidiGain	= (uint32_t)Dataspace::GainUnit::midi
	};
	

} // namespace Jamoma

