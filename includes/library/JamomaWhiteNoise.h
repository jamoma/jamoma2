/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generate random samples to produce noise.
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"
#include "MersenneTwister.h"


namespace Jamoma {
	
	/**	This AudioObject generates <a href="https://en.wikipedia.org/wiki/White_noise">white noise</a> by filling a Sample or SampleBundle with random values.
		These values are generated using the <a href="https://en.wikipedia.org/wiki/Mersenne_Twister">Mersenne Twister algorithm</a>.
	 */
	class WhiteNoise : public AudioObject {
		
		MTRand	mTwister;	///< Class implementing Mersenne Twister algorithm
		
	public:
		static constexpr Classname classname = { "noise" };
		static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "noise" };
		
        /** Process one sample.
         @param	x	Sample to be processed.
         @return		Processed sample
         */
		Sample operator()(Sample x)
		{
			return mTwister.rand(2.0) - 1.0;
		}
		
        /** Process a SharedSampleBundleGroup.
         @param	x	SharedSampleBundleGroup to be processed.
         @return		Processed SharedSampleBundleGroup.
         */
		SharedSampleBundleGroup operator()(const SampleBundle& x = kSampleBundleNone)
		{
			auto out = mOutput;

			for (int channel=0; channel < out.channelCount(); ++channel)
				for	(auto& sample : out[0][channel])
					sample = (*this)(0.0);
			return out;
		}
		
	};
	
} // namespace Jamoma
