/** @file
	
	@ingroup 	jamoma2
	
	@brief 		IIR comb filter
	
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"
#include "JamomaLowpassOnepole.h"

namespace Jamoma {

	
	/**	This AudioObject implements an IIR comb filter with an additional lowpass filter in the feedback loop.
		The result is a comb filter that is warmer or "less tinny" than the typical comb filter.
		This filter is one of the key building blocks in for the TapVerb effect.
	 */
	class Comb : public AudioObject {

		
		const std::size_t			mCapacity;
//		CircularSampleBufferGroup	mFeedforwardHistory;
//		Delay			mFeedbackBuffer;
		CircularSampleBufferGroup	mFeedbackHistory;
		LowpassOnePole				mLowpassFilter;
		Observer					mChannelCountObserver = { std::bind(&Comb::resizeHistory, this) };

		void resizeHistory() {
			if ((mFeedbackHistory.size() && mFeedbackHistory[0].size() != size+frameCount) || mFeedbackHistory.size() != (size_t)channelCount) {
				mFeedbackHistory.clear(); // ugly: doing this to force the reconstruction of the storage to the correct size
				mFeedbackHistory.resize(channelCount, std::make_pair(mCapacity+frameCount, (size_t)size+frameCount));
			}
		}
		
		
	public:
		static constexpr Classname classname = { "comb" };
		static constexpr auto tags = { "dspFilterLib", "audio", "processor", "filter", "comb" };
	
		
		/** TODO: Make capacity dynamic?  It already sort of is when the channel count changes...
		 */
		Comb(std::size_t capacity = 4410)
		: mCapacity(capacity)
		, mFeedbackHistory(1, capacity)
		{
			channelCount.addObserver(mChannelCountObserver);
		}

		
		/** size of the history buffers -- i.e. the delay time
			TODO: dataspace integration for units other than samples
		 */
		Parameter<int>	size = { this, "size", 1,
								[this]{
									for (auto& channel : mFeedbackHistory)
										channel.resize((int)size);
								}
		};
		
		
		/** Delay time.
			An alias of the #size parameter.
			TODO: dataspace with Native Unit in samples
		 */
		Parameter<int>		delay = { this, "delay", 1, [this] { size = (int)delay; } };
	
		
		/** Decay time -- is this really a dataspace conversion of the feedback coefficient?  maybe not...
		 */
		Parameter<double>	decay = { this, "decay", 0.0,
			[this]{
				//				mDeciResonance = resonance * 0.1;
				//				calculateCoefficients();
			}
		};
		
	
		/** Feedback coefficient.
         */
		Parameter<double>	feedback = { this, "feedback", 0.0,
			[this]{
//				mDeciResonance = resonance * 0.1;
//				calculateCoefficients();
			}
		};


		/** Clip the feedback internally to prevent the possibility of the filter blowing-up.
		 */
		Parameter<bool>		clip = {this, "clip", true, };

		
		/** Cutoff Frequency for the internal lowpass filter
		 */
		Parameter<double>	cutoff = { this, "cutoff", 0.0,
			[this]{
				mLowpassFilter.frequency = (double)cutoff;
				//				mDeciResonance = resonance * 0.1;
				//				calculateCoefficients();
			}
		};
		
		
		
		Message			setDelayIndependently = { "setDelayIndependently",
													Synopsis("Set the delay parameter without recalculating decay times or other dependent parameters."),
													[this]{
														// TODO: implement
														;
													}
		};
		
		
		/**	This algorithm is an IIR filter, meaning that it relies on feedback.  If the filter should
			not be producing any signal (such as turning audio off and then back on in a host) or if the
			feedback has become corrupted (such as might happen if a NaN is fed in) then it may be
			neccesary to clear the filter by calling this method.											
		 */
		Message			clear = { "clear",
									Synopsis("Reset the Filter History"),
									[this]{
										mFeedbackHistory.clear();
										mLowpassFilter.clear();
									}
		};
		
		
		

		
		Sample operator()(Sample x)
		{
			return (*this)(x, 0);
		}
		
		
		Sample operator()(Sample x, int channel)
		{
            Sample y = x;
						
			return y;
		}
		
		
		SharedSampleBundleGroup operator()(const SampleBundle& x)
		{
			auto out = adapt(x);
			
			for (int channel=0; channel < x.channelCount(); ++channel) {
				for	(int i=0; i < x.frameCount(); ++i)
					out[0][channel][i] = (*this)(x[channel][i], channel);
			}
			return out;
		}
		
	};
	

} // namespace Jamoma
