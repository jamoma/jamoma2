/** @file
	
	@ingroup jamoma2
	
	@brief Block DC offset within samples.
		
	@author Timothy Place, Nathan Wolek
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {

	
	/**	This AudioObject removes DC offset (sometimes called <a href="https://en.wikipedia.org/wiki/DC_bias">DC bias</a> from a Sample or SampleBundle.
		The process is acheived by applying a first-order highpass filter to the input.
	 */
	class Dcblock : public AudioObject {
		
		AdaptingSampleBundle	mX = { this };	// input history -- AdaptingSampleBundle type will update channelCount automagically as needed
		AdaptingSampleBundle	mY = { this };	// output history -- AdaptingSampleBundle type will update channelCount automagically as needed
		
	public:
		static constexpr Classname classname = { "dcblock" };
		static constexpr auto tags = { "dspFilterLib", "audio", "filter" };
		
		
		Message			clear = { "clear", [this]{
									mX.fill(0.0);
									mY.fill(0.0);
								}
		};
		
		
		Sample operator()(Sample x)
		{
			return (*this)(x, 0);
		}
		
		
		Sample operator()(Sample x, int channel)
		{
			Sample y = x - mX[channel][0] + (mY[channel][0] * 0.9997);
			//TODO: TTZeroDenormal(y);
			mY[channel][0] = y;
			mX[channel][0] = x;
			return y;
		}
		
		
		SharedSampleBundleGroup operator()(const SampleBundle& x)
		{
			auto out = mOutput;
			out.adapt(x);
			channelCount = (int)x.channelCount();
			
			for (int channel=0; channel < x.channelCount(); channel++) {
				for	(int i=0; i < x.frameCount(); i++)
					out[0][channel][i] = (*this)(x[channel][i], channel);
			}
			return out;
		}

	};

} // namespace Jamoma
