/** @file
	
	@ingroup jamoma2
	
	@brief Lookahead limiter processor for controlling the dynamics of an input.
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"
#include "JamomaDcblock.h"
#include "JamomaGain.h"


namespace Jamoma {

	
	/**	TTLimiter implements a lookahead limiter processor for controlling the dynamics of an input.
	 
		The way this works is by buffering the input, and delaying it by N samples.
		That way we are able to see what the output will be some amount of time prior to actually outputting it,
		and adjust the gain accordingly.

		After some preprocessing to adjust gain and filter DC offsets on the input, we have an analysis stage.
		The analysis stage looks at the sample value for each channel at the input,
		and then uses the hottest sample to calculate the gain adjust that needs to be applied.

		The release attribute (specified in seconds) determines how long it takes for a gain reduction to "wear off"
		once the amplitude level of the input has been reduced.
	 
		TODO: Can lookahead be implemented now using the CircularStorage class?
	 */
	class Limiter : public AudioObject {
		static constexpr Classname classname = { "limiter" };
		static constexpr auto tags = { "dspEffectsLib", "audio", "processor", "dynamics", "limiter" };

		AdaptingSampleBundle	mLookaheadBuffer;			///< keep a lookahead buffer for each channel
		AdaptingSampleBundle	mGain;						///< keep a gain for each channel
		
		Dcblock					mDcblockerObject;
		Gain					mPreampObject;

		double					recover = 0.0;				///<
		double					lookaheadInv = 0.0;			///< reciprocal (inverse) of the lookahead attribute
		int						lookaheadBufferIndex = 0;
		Sample					last = 0.0;
		int						maxBufferSize = 512;		///< TODO: make this settable

		
	public:
		// Two representations of the same thing -- we assign a hash of the string representation for the dynamic access
		enum class Mode {
			linear			= Hash("linear"),
			exponential		= Hash("exponential")
		};
		Parameter<Mode>		mode = {this, "mode", Mode::linear,
									[this] {
										setRecover();
									}
		};	///< may be one of two symbols: "linear" or "exponential".
		

		// TODO: we need a listener to receive notifications for sample rate changes -- it needs to call setRecover();
		
		
		// linear gain scaling factor prior to limiting (attr setter used dB).
		Parameter<double>	preamp = {this, "preamp", 0_db,
										[this]{
											mPreampObject.gain = (double)preamp;
										}
		};
		
		
//		bool			isLinear;				///< is attrMode set to linear?
//		AudioObject		dcBlocker;				///< #TTDCBlock object
//		AudioObject		preamp;					///< #TTGain object to apply preamp
		
//		bool			attrDCBlocker;								///< If toggled to NO, the internal DC Blocker will be turned off.
		Parameter<bool>		blockdc = {this, "blockdc", true};		///< If toggled to NO, the internal DC Blocker will be turned off.
		
		
		// TODO: make this a chrono-based parameter
		//double			attrRelease;							///< number of seconds for the release to recover after a peak in the audio signal.
		Parameter<double>	release = {this, "release", 1000.0,
			[this]{
				setRecover();
			}
		};
		
		
		//int				attrLookahead;							///< number of samples by which to look forward.
		Parameter<int>		lookahead = {this, "lookahead", 100,
			[this]{
				lookahead = Limit<int>(lookahead, 1, maxBufferSize-1);
				lookaheadInv = 1.0 / double(lookahead);
			}
		};
		
		
		//double			attrThreshold;							///< linear amplitude threshold at which the limiting should kick in (attr setter used dB).
		Parameter<double>	threshold = {this, "threshold", 0_db};
		
		
		//double			attrPostamp;							///< linear gain scaling factor after the limiting (attr setter used dB).
		Parameter<double>	postamp = {this, "postamp", 0_db};
	
		
		/** Clear the history: reset the limiter. */
		Message			clear = { "clear",
									Synopsis("Reset the Filter History"),
									[this]{
										for (int i=0; i<maxBufferSize; i++) {
											for (int channel=0; channel < channelCount; channel++)
												mLookaheadBuffer[channel][i] = 0.0;
											mGain[0][i] = 1.0;		// gain is shared across channels
										}
										
										lookaheadBufferIndex = 0;	// was bp
										last = 1.0;
										setRecover();
										
										mDcblockerObject.clear();
									}
		};


		Sample operator()(Sample x)
		{
			assert(false); // single-sample function is inappropriate for the Limiter
			return 0.0;
		}


		SharedSampleBundleGroup operator()(const SampleBundle& x) override
		{
			// adapting and preprocessing is handled below in the SharedSampleBundleGroup function operator
			
			Sample		hotSample = 0.0;
			Sample		tempSample;
			double		maybe;
			double		curgain;
			double		newgain;
			double		inc;
			double		acc;
			int			flag;
			int			lookaheadBufferPlayback;
			int			ind;
		
			for (int i=0; i < x.frameCount(); i++) {
				
				// Analysis Stage ...
				for (int channel=0; channel < x.channelCount(); channel++) {
					tempSample = x[channel][i];
					
					mLookaheadBuffer[channel][lookaheadBufferIndex] = tempSample * postamp;
					tempSample = fabs(tempSample);
					if (tempSample > hotSample)
						hotSample = tempSample;
				}
				
				if (mode == Mode::linear)
					tempSample = last + recover;
				else {
					if (last > 0.01)
						tempSample = last + recover * last;
					else
						tempSample = last + recover;
				}
				
				if (tempSample > threshold)
					maybe = threshold;
				else
					maybe = tempSample;
				mGain[0][lookaheadBufferIndex] = maybe;
				
				lookaheadBufferPlayback = lookaheadBufferIndex - lookahead;
				if (lookaheadBufferPlayback < 0)
					lookaheadBufferPlayback += lookahead;
				
				// Process Stage ...
				// this ***very slow*** : with a lookahead of 100, and vs = 64, we loop 640 times!
				if (hotSample * maybe > threshold) {
					curgain = threshold / hotSample;
					inc = (threshold - curgain);
					acc = 0;
					flag = 0;
					for (int j=0; flag==0 && j<lookahead; j++) {
						ind = lookaheadBufferIndex - j;
						if (ind<0)
							ind += maxBufferSize;
						
						if (mode == Mode::linear) //TODO: can't we move this condition outside the loop? isLinear won't change during a vs [NP]
							newgain = curgain + inc * acc;
						else
							newgain = curgain + inc * (acc * acc);
						
						if (newgain < mGain[0][ind])
							mGain[0][ind] = newgain;
						else
							flag = 1;
						acc = acc + lookaheadInv;
					}
				}
				
				// Actual application of the gain
				for (int channel=0; channel < x.channelCount(); channel++)
					mOutput[0][channel][i] = mLookaheadBuffer[channel][lookaheadBufferPlayback] * mGain[0][lookaheadBufferPlayback];
				
				last = mGain[0][lookaheadBufferIndex];
				lookaheadBufferIndex++;
				if (lookaheadBufferIndex >= lookahead)
					lookaheadBufferIndex = 0;
			}
			return mOutput;
		}
		
		
		SharedSampleBundleGroup operator()(const SharedSampleBundleGroup x) override
		{
			SharedSampleBundleGroup out = mOutput;
			SharedSampleBundleGroup temp;
			
			// Adapt to the source channels and blocksize
			channelCount = (int)x.channelCount();
			out.adapt(x);

			// Pre-Process the input
			if (blockdc) {
				out = mDcblockerObject(x);
				temp = mPreampObject(out);
			}
			else
				temp = mPreampObject(x);

			out = mPreampObject(temp);
			
			return (*this)(temp[0]); // call the above SampleBundle function operator
		}

		
	private:
		// set variables related to the time it takes for the limiter to recover from a peak in the audio
		// it is based on the release time attr, which is specified in seconds
		void setRecover()
		{
			recover = 1000.0 / (release * sampleRate);
			if (mode == Mode::linear)
				recover = recover * 0.5;
			else
				recover = recover * 0.707;
		}

		
	};
	

} // namespace Jamoma
