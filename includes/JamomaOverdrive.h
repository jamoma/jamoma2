/** @file
 *
 * @ingroup jamoma2
 *
 * @brief Apply a soft saturation distortion effect to samples.
 *
 * @details This #AudioObject "warms" the signal by applying a small amount of <a href="https://en.wikipedia.org/wiki/Distortion_(music)">distortion</a> to a #Sample or #SampleBundle. 
 * It contains two options for the underlying processing algorithm and three options for clipping the initial input.
 *
 * @author Timothy Place, Nathan Wolek
 *
 * @warning This class is a stub.
 *
 * @copyright Copyright © 2015 by Jamoma authors and contributors @n
 * This code is licensed under the terms of the "BSD 3-Clause License" @n
 * https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"

namespace Jamoma {
	
	/*
	class Overdrive : public AudioObject {
	public:
		
		static constexpr auto classname = { "overdrive" };
		
		
		Message				clear = { "clear",
									[this](const ValueBase& input){
										//return dcblocker.send("clear");
										return dcblocker.clear();
									}
		};
		
		
		Parameter<int>		mode = { this,								// zeroeth arg is always pointer to this
									"mode",								// first arg is always name
									1,									// second arg is always default value
									Synopsis("Distortion function")		// additional args can come in any order
		};
		
		
		Parameter<bool>		blockdc = { this,
										"blockdc",
										true,
										[this](const auto& input){		// this optional arg is a custom setter
											blockdc = input;			// store new value to ourselves
											dcblocker.bypass = blockdc; // set attr on dcblocker object (this one inherited from AudioObject)
										}
		};
		
		
		Parameter<int>		channelCount = { this, "channelCount", 1,
											[this](const auto& input){
												channelCount = input;
												dcblocker.channelCount = channelCount;
											}
		};
		
		
		//object			dcblocker = {"dcblock"};					// dynamic way (like what we've always done, but better)
		Dcblock				dcblocker;									// direct instantiation (allows inlining, compile-time error checking, etc.)
		
		
		Parameter<double>	preamp = { this,
										"preamp",
										0.0,
										[this](const auto& input){		// setter
											preamp = DecibelsToLinearGain(input);
										},
										[this]()->Value<double> {				// getter
											return LinearGainToDecibels(preamp);
										}
		};
		
		
		Parameter<double>	drive = { this,
										"drive",
										3.0,
										Boundaries<double>(1.0, 10.0),
										BoundaryBehavior::clip,				// hopefully this one is self explanatory :-)
										[this](const auto& input){			// a more involved setter
											drive = input;
											
											// These calculations really only apply to mode 1...
											double f = (drive - 0.999) * 0.111;	// range is roughly [0.001 to 0.999]
											
											z = M_PI * f;
											s = 1.0 / sin(z);
											b = 1.0 / f;
											Limit(b, 0.0, 1.0);
											nb = b * -1.0;
											int i = int(f);
											if ((f-(double)i) > 0.5)
												scale = sin(z); // sin(f * kTTPi);
												else
													scale = 1.0;
										}
		};
		
	private:
		double				s, b, nb, z, scale;
	};
*/
	
	
	
	
	
	//		SampleFunction	sampleCalc = { [this](const Sample x, int channel) -> Sample {
	//											Sample y = x - mX[channel][0] + mY[channel][0] * 0.9997;
	//											return y;
	//										}
	//		};
	
	
	//		VectorFunction	vectorCalc = { [this](const SampleBundle& in) -> auto {
	//											auto out = std::make_unique<SampleBundle>();
	//
	//											for (int channel=0; channel<in.channelCount(); channel++)
	//												std::transform(in[channel].begin(), in[channel].end(), out->at(channel).begin(), sampleCalc);
	//
	//												return out;
	//										}
	//		};
	
	

}




/*
 
 
 TTErr TTOverdrive::processMode0(TTAudioSignalArrayPtr inputs, TTAudioSignalArrayPtr outputs)
 {
	TTAudioSignal&	in = inputs->getSignal(0);
	TTAudioSignal&	out = outputs->getSignal(0);
	TTUInt16		vs;
	TTSampleValue	*inSample,
 *outSample;
	TTChannelCount	numchannels = TTAudioSignal::getMinChannelCount(in, out);
	TTChannelCount	channel;
	TTSampleValue	temp,
 sign;
 
	dcBlockerUnit.process(in, out);
 
	for (channel=0; channel<numchannels; channel++) {
 inSample = in.mSampleVectors[channel];
 outSample = out.mSampleVectors[channel];
 vs = in.getVectorSizeAsInt();
 
 while (vs--) {
 temp = *inSample++ * mPreamp;
 
 // the equation only works in the positive quadrant...
 // so we strip off the sign, apply the equation, and reapply the sign
 if (temp < 0.0) {
 temp = -temp;
 sign = -1.0;
 }
 else
 sign = 1.0;
 
 if (temp > 1.0)		// clip signal if it's out of range
 *outSample++ = TTClip(temp * sign, TTSampleValue(-1.0), TTSampleValue(1.0));
 else
 *outSample++ = sign * (1.0 - exp(mDrive * log(1.0 - temp)));
 }
	}
	return kTTErrNone;
 }
 
 
 TTErr TTOverdrive::processMode1(TTAudioSignalArrayPtr inputs, TTAudioSignalArrayPtr outputs)
 {
	TTAudioSignal&	in = inputs->getSignal(0);
	TTAudioSignal&	out = outputs->getSignal(0);
	short			vs;
	TTSampleValue	*inSample,
 *outSample;
	TTChannelCount	numchannels = TTAudioSignal::getMinChannelCount(in, out);
	TTChannelCount	channel;
	TTSampleValue	temp;
 #ifdef TT_PLATFORM_WIN
	TTSampleValue	sign;
 #endif
	
	dcBlockerUnit.process(in, out);
 
	for (channel=0; channel<numchannels; channel++) {
 inSample = in.mSampleVectors[channel];
 outSample = out.mSampleVectors[channel];
 vs = in.getVectorSizeAsInt();
 
 while (vs--) {
 temp = *inSample++ * mPreamp;
 if (temp > b)
 temp = 1.0;
 else if (temp < nb)
 temp = -1.0;
	#ifdef TT_PLATFORM_WIN
 else {
 // http://redmine.jamoma.org/issues/show/54
 // It is insane, but on Windows sin() returns bad values
 // if the argument is negative, so we have to do this crazy workaround.
 if (temp < 0.0) {
 temp = -temp;
 sign = -1.0;
 }
 else
 sign = 1.0;
 temp = sign * sin(z * temp) * s;
 // instead of using this more simple solution:
 //temp = (z * temp) * s;
 }
	#else
 else
 temp = sin(z * temp) * s;
	#endif
 *outSample++ = temp * scale;
 }
	}
	return kTTErrNone;
 }
 

 
 */
