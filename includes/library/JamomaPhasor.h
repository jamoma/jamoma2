/** @file
	
	@ingroup 	jamoma2
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {

	
	/**	Phasor object -- a non-bandlimited ramp wave oscillator.
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
				mPhase = 0.0;
			else if (mPhase < 0.0)
				mPhase = 1.0;
			
			Sample y = mPhase * gain + offset;
			
			mPhase += mStep;
			return y;
		}
		
		
		/** Process a SharedSampleBundleGroup.
			@param	x	SharedSampleBundleGroup to be processed.
			@return		Processed SharedSampleBundleGroup.
		 */
		SharedSampleBundleGroup operator()(const SampleBundle& x)
		{
			auto out = adapt(x);

			for (int channel=0; channel<x.channelCount(); ++channel)
				std::transform(x[channel].begin(), x[channel].end(), out[0][channel].begin(), *this);
			return out;
		}
		
	};

} // namespace Jamoma
