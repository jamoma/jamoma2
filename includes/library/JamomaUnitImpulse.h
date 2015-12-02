/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generate one sample at maximum amplitude for testing.
	
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {
    
    /** This AudioObject generates a unit impulse function (sometimes called  <a href="https://en.wikipedia.org/wiki/Dirac_delta_function">Dirac function</a> by setting the initial Sample to one and filling the remainder of the SampleBundle with zeros.
        This function is typically used to test the <a href="https://en.wikipedia.org/wiki/Impulse_response">impulse response</a> of a time-invariant filter.
     */
    class UnitImpulse : public AudioObject {
    
        
    public:
        static constexpr Classname classname = { "unitimpulse" };
        static constexpr auto tags = { "dspGeneratorLib, audio, generator, impulse" };
		
        /** Process one sample.
         @param	x	Sample to be processed.
         @return		Processed sample
         */
        Sample operator()(Sample x)
        {
            return 1.0;
        }
		
        /** Process a SharedSampleBundleGroup.
         @param	x	SharedSampleBundleGroup to be processed.
         @return		Processed SharedSampleBundleGroup.
         */
        SharedSampleBundleGroup operator()(const SampleBundle& x = kSampleBundleNone)
        {
            auto out = mOutput;
            
            for (int channel=0; channel < channelCount; ++channel) {
                out[0][channel][0] = 1.0;
                for	(int i=1; i < x.frameCount(); ++i)
                    out[0][channel][i] = 0.0;
            }
            return out;
        }
    };
    

} // namespace Jamoma
