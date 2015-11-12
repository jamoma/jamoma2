/** @file
	
	@ingroup	jamoma2
	
	@brief		Generic IIR allpass filter
	
	@author 	Timothy Place, Trond Lossius
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"
#include "JamomaLowpassOnepole.h"

namespace Jamoma {

	
	/**	This AudioObject implements a generalized allpass filter.
	 */
	class Allpass1 : public AudioObject {
		
		const std::size_t			mCapacity;
		CircularSampleBufferGroup	mFeedforwardHistory;
		CircularSampleBufferGroup	mFeedbackHistory;
		Observer					mChannelCountObserver = { std::bind(&Allpass1::resizeHistory, this) };

		void resizeHistory() {
			if ((mFeedbackHistory.size() && mFeedbackHistory[0].size() != size+frameCount) || mFeedbackHistory.size() != (size_t)channelCount) {
				mFeedforwardHistory.clear();
				mFeedbackHistory.clear(); // ugly: doing this to force the reconstruction of the storage to the correct size
				mFeedforwardHistory.resize(channelCount, std::make_pair(mCapacity+frameCount, (size_t)size+frameCount));
				mFeedbackHistory.resize(channelCount, std::make_pair(mCapacity+frameCount, (size_t)size+frameCount));
			}
		}
		
	public:
		static constexpr Classname classname = { "allpass.1" };
		static constexpr auto tags = { "dspFilterLib", "audio", "processor", "filter", "allpass" };
		
		
		/** TODO: Make capacity dynamic?  It already sort of is when the channel count changes...
		 */
		Allpass1(std::size_t capacity = 4410)
		: mCapacity(capacity)
		, mFeedforwardHistory(1, capacity)
		, mFeedbackHistory(1, capacity)
		{
			channelCount.addObserver(mChannelCountObserver);
		}

		
		/** size of the history buffers -- i.e. the delay time
			TODO: dataspace integration for units other than samples
		 */
		Parameter<int>	size = { this, "size", 1,
								Setter([this]{
									for (auto& channel : mFeedforwardHistory)
										channel.resize((int)size);
									for (auto& channel : mFeedbackHistory)
										channel.resize((int)size);
								})
		};

		
		/** Delay time.
			An alias of the #size parameter.
			TODO: dataspace with Native Unit in samples
         */
		Parameter<int>		delay = { this, "delay", 1, Setter([this] { size = (int)delay; }) };
		
	
		/** Feedback coefficient.
         */
		Parameter<double>	gain = { this, "gain", 0.0 };

		
		/**	This algorithm is an IIR filter, meaning that it relies on feedback.  If the filter should
			not be producing any signal (such as turning audio off and then back on in a host) or if the
			feedback has become corrupted (such as might happen if a NaN is fed in) then it may be
			neccesary to clear the filter by calling this method.											
		 */
		Message			clear = { "clear",
									Synopsis("Reset the Filter History"),
									[this]{
										for (auto& channel : mFeedforwardHistory)
											channel.clear();
										for (auto& channel : mFeedbackHistory)
											channel.clear();
									}
		};

		
		Sample operator()(Sample x)
		{
			return (*this)(x, 0);
		}
		
		
		Sample operator()(Sample x, int channel)
		{
			Sample x1 = mFeedforwardHistory[channel].tail(-1);
			Sample y1 = mFeedbackHistory[channel].tail(-1);
			Sample alpha = gain;
			
			// Store the input in the feedforward buffer
			mFeedforwardHistory[channel].write(x);
			
			// Apply the filter
			// We start with the equation in standard form:
			//		y = alpha * x  +  x1  -  alpha * y1;
			// Then to a version that Fred Harris refers to as a "Re-Ordered All-Pass Filter Structure" in Multirate Signal Processing
			//		y = x1  +  alpha * x  -  alpha * y1;
			// Finally, here is a "Single Coefficient All-Pass Filter", dropping from 2 adds and 2 mults down to 2 adds and 1 mult
			Sample y = x1 + ((x - y1) * alpha);

			// The possibility of denormals is always lurking for IIR filters
			ZeroDenormal(y);
			
			// Store the output in the feedback buffer
			mFeedbackHistory[channel].write(y);
			
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
