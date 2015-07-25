//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

#pragma once

#include "JamomaAudioObject.h"
#include "MersenneTwister.h"


namespace Jamoma {
	
	class Noise : public AudioObject {
		
		MTRand	mTwister;	///< Class implementing Mersenne Twister algorithm
		
	public:
		static constexpr Classname classname = { "noise" };
		static constexpr auto tags = { "dspGeneratorLib, audio, generator, noise" };
		
		
		Sample operator()(Sample x)
		{
			return mTwister.rand(2.0) - 1.0;
		}
		
		
		SharedSampleBundleGroup operator()(const SampleBundle& x = kSampleBundleNone)
		{
			auto out = mOutput;

			for (int channel=0; channel < out.channelCount(); channel++)
				for	(auto& sample : out[0][channel])
					sample = (*this)(0.0);
			return out;
		}
		
	};
	
} // namespace Jamoma
