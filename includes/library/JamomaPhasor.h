/** @file
	
	@ingroup 	jamoma2
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {

	
	/**	This AudioObject generates a non-bandlimited <a href="https://en.wikipedia.org/wiki/Sawtooth_wave">sawtooth wave</a> oscillator. 
        This function is typically used as a control signal for <a href="https://en.wikipedia.org/wiki/Phase_(waves)">phase</a> ramping.
	 */
	class Phasor : public AudioObject {
		double	mPhase = 0.0;
		double	mStep = 0.0;
		
		void setStep()
		{
            mStep = frequency / sampleRate;
			ZeroDenormal(mStep);
		}

		
	public:
		static constexpr Classname classname = { "phasor" };
		static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "oscillator" };
		

		Parameter<double, Limit::Wrap<double>, NativeUnit::None<double>>	phase		= { this,
																						"phase",
																						0.0,
																						Range<double>(0.0, 1.0),
																						Setter([this]{
																							mPhase = phase;
																						})
		};
		

		Parameter<double, Limit::Fold<double>, NativeUnit::None<double>>	frequency	= {	this,
																						"frequency",
																						1.0,
																						Range<double>(sampleRate * -0.5, sampleRate * 0.5),
																						Setter( [this]{
																							setStep();
																						} ),
																						Synopsis("Rate at which to cycle")
		};

		
		Parameter<double, Limit::None<double>, NativeUnit::LinearGain>		gain = { this, "gain", 1.0 };		///< scaling applied to the output

		
		Parameter<double>													offset = { this, "offset", 0.0 };	///< shift applied to the output

		

		
		// TODO: add offset Parameter from Jamoma1
		// TODO: add gain Parameter from Jamoma1
		
		
		/** Process one sample.
			@param	x	Sample to be processed.
			@return		Processed sample
		 */
		Sample operator()(const Sample x)
		{
			if (mPhase > 1.0)
				mPhase -= 1.0;
			else if (mPhase < 0.0)
				mPhase += 1.0;
			
			Sample y = mPhase * gain + offset;
			
			mPhase += mStep;
			return y;
		}
		
		
		/** Process a SharedSampleBundleGroup.
			@param	x	SharedSampleBundleGroup to be processed.
			@return		Processed SharedSampleBundleGroup.
		 */
		SharedSampleBundleGroup operator()(const SampleBundle& x = kSampleBundleNone)
		{
			auto out = mOutput;

			for (int channel=0; channel<x.channelCount(); ++channel)
                for	(auto& sample : out[0][channel])
                    sample = (*this)(0.0);
			return out;
		}
		
	};

} // namespace Jamoma
