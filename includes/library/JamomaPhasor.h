/** @file
	
	@ingroup jamoma2
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {

	
	/**	Phasor object -- a non-bandlimited ramp wave oscillator.
	 */
	class Phasor : public AudioObject {
		double	mPhase = 0.0;
		double	mStep = 0.0;
		long	mRampSamples = 0;
		
		void setStep()
		{
			mStep = 1.0 / double(mRampSamples - 1.0);	// 1.0 is the destination
			if (frequency < 0)
				mStep = -mStep;
			ZeroDenormal(mStep);
		}

		
	public:
		static constexpr Classname classname = { "phasor" };
		static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "oscillator" };
		

		Parameter<double, NativeUnit::None<double>, RangeLimit::wrap>	phase		= { this,
																						"phase",
																						0.0,
																						Range<double>(0.0, 1.0),
																						[this]{
																							mPhase = phase;
																							if (frequency < 0)
																								mPhase += 1.0;
																						}
		};
		

		Parameter<double, NativeUnit::None<double>, RangeLimit::fold>	frequency	= {	this,
																						"frequency",
																						1.0,
																						Range<double>(0.0, sampleRate * 0.5),
																						[this]{
																							double lFrequency = frequency;
																							if (lFrequency == 0)
																								mRampSamples = 0xFFFFFFFF;
																							else
																								mRampSamples = long(sampleRate / fabs(lFrequency));
																							setStep();
																						}
		};

		
		Parameter<double, NativeUnit::LinearGain>						gain = { this, "gain", 1.0 };		///< scaling applied to the output

		
		Parameter<double>												offset = { this, "offset", 0.0 };	///< shift applied to the output

		

		
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

			for (int channel=0; channel<x.channelCount(); channel++)
				std::transform(x[channel].begin(), x[channel].end(), out[0][channel].begin(), *this);
			return out;
		}
		
	};

} // namespace Jamoma
