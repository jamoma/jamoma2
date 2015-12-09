/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Apply a first-order low-pass filter to samples.
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"

namespace Jamoma {
    
    /**	This AudioObject applies a basic <a href="https://en.wikipedia.org/wiki/Low-pass_filter">low-pass filter</a> to a Sample or SampleBundle.
		Handy for use in smoothing control signals or damping high frequency components.
     */
    class LowpassOnePole : public AudioObject {
        
        AdaptingSampleBundle		mY1 = {this};           ///< previous output sample (for each channel)
        double                      mA0;					///< gain coefficient
        double                      mB1;					///< feedback coefficient
        
    public:
        static constexpr Classname classname = { "lowpass.1" };
        static constexpr auto tags = { "dspEffectsLib", "audio", "processor", "filter", "lowpass" };
		
		
        /** Filter coefficient. */
		Parameter<double, Limit::Clip<double>, NativeUnit::None<double>> coefficient = { this,
                                                            "coefficient",
                                                            0.5,
                                                            Range<double>(0.0, 1.0),
                                                            Setter([this]{
                                                                mA0 = coefficient;
                                                                mB1 = 1 - coefficient;
                                                            })
        };
		
		
		/** Set filter coefficient using a cutoff frequency.
			@see http://musicdsp.org/showArchiveComment.php?ArchiveID=237
		 */
		Parameter<double, Limit::None<double>, NativeUnit::Hz> frequency = { this, "frequency", 1000.0,
			Setter([this]{coefficient = 1.0 - exp(-2.0 * 3.1415 * frequency / sampleRate);})
		};
		
		
		/**	This algorithm is an IIR filter, meaning that it relies on feedback.  If the filter should
			not be producing any signal (such as turning audio off and then back on in a host) or if the
			feedback has become corrupted (such as might happen if a NaN is fed in) then it may be
			neccesary to clear the filter by calling this method.
		 */
		Message clear = {	"clear",
							Synopsis("Reset the Filter History"),
							[this]{
								mY1.fill(0.0);
							}
		};
		
		
        Sample operator()(Sample x)
        {
            return (*this)(x,0);
        }
		
		
        Sample operator()(Sample x, int channel)
        {
            Sample y = (x * mA0) + (mY1[channel][0] * mB1); // compute next output sample

			ZeroDenormal(y);
			mY1[channel][0] = y; // update history
            return y;
        }
		
		
        SharedSampleBundleGroup operator()(const SampleBundle& x)
        {
            auto out = adapt(x);
			
            for (int channel=0; channel < x.channelCount(); ++channel) {
                for (int i=0; i < x.frameCount(); ++i)
                    out[0][channel][i] = (*this)(x[channel][i], channel);
            }
            
            return out;
        }
        
    };
    
    
}  // namespace Jamoma
