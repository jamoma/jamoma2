//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {

	class Gain : public AudioObject {
	public:
		static constexpr Classname classname = { "gain" };
		static constexpr auto tags = { "dspEffectsLib", "audio", "processor", "dynamics" };
		

		Parameter<double>	gain = { this, "gain", 1.0 /*, Dataspace::Gain */ };

		
		Sample operator()(const Sample x)
		{
			return x * gain;
		}
		
		
		SharedSampleBundle operator()(const SampleBundle& x)
		{
			auto out = mOutput;
			out->adapt(x);
			for (int channel=0; channel<x.channelCount(); channel++)
				std::transform(x[channel].begin(), x[channel].end(), out->at(channel).begin(), *this);
			return out;
		}
		
		
		SharedSampleBundle operator()(const SharedSampleBundle& x)
		{
			return (*this)(*x);
		}
	};

}
