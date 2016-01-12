/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generate a basic, cycling waveform using an internal lookup table.
	
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {
    
    /**	This AudioObject generates a basic <a href="https://en.wikipedia.org/wiki/Waveform">waveform</a> by filling an internal SampleBundle with the shape to be repeated at a given frequency.
     This method of sound generation is typically referred to as <a href="https://en.wikipedia.org/wiki/Table-lookup_synthesis">table-lookup</a> or <a href="https://en.wikipedia.org/wiki/Wavetable_synthesis">wavetable</a> synthesis.
     */
    class Waveform : public AudioObject {
    public:
        static constexpr Classname classname = { "waveform" };
        static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "waveform", "wavetable" };
        
    private:
        
    };

} // namespace Jamoma