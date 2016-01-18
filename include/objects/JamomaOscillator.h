/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generate a basic, periodic waveform using an internal lookup table.
	
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"
#include "JamomaSync.h"


namespace Jamoma {
    
    /**	This AudioObject generates a <a href="https://en.wikipedia.org/wiki/Waveform">periodic waveform</a> by filling an internal SampleBundle with the shape to be repeated at a given frequency.
     This method of sound generation is typically referred to as <a href="https://en.wikipedia.org/wiki/Table-lookup_synthesis">table-lookup</a> or <a href="https://en.wikipedia.org/wiki/Wavetable_synthesis">wavetable</a> synthesis.
     */
    class Oscillator : public AudioObject {
    public:
        static constexpr Classname classname = { "oscillator" };
        static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "oscillator", "wavetable" };
        
        /** Table size is fixed at instantiation
         */
        Oscillator(std::size_t tableSize = 8192)
        : mLookupTable(1, tableSize)
        {
            // NW: Do we need observers here?
        }
        
    private:
        Jamoma::Sync                mSync;
        Jamoma::SampleBundle        mLookupTable;
    };

} // namespace Jamoma