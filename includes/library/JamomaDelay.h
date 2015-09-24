/** @file
	
	@ingroup jamoma2
	
	@brief Delay line implementations
	
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"

namespace Jamoma {

	
	/**	A multichannel non-interpolating delay line.
		TODO: make this a template class specialized with an interpolation template parameter?
	 */
	class Delay : public AudioObject {
		
		const std::size_t			mCapacity;
		CircularSampleBufferGroup	mHistory;

		Observer				mChannelCountObserver = Function( [this]{
			if ((mHistory.size() && mHistory[0].size() != size+frameCount) || mHistory.size() != (size_t)channelCount) {
																			mHistory.clear(); // ugly: doing this to force the reconstruction of the storage to the correct size
																			mHistory.resize(channelCount, std::make_pair(mCapacity+frameCount, (size_t)size+frameCount));
			}
		} );

	public:
		static constexpr Classname classname = { "delay" };
		static constexpr auto tags = { "dspEffectsLib", "audio", "processor", "delay" };
		
		
		/** Capacity of the delay is fixed at instantiation
		 */
		Delay(std::size_t capacity = 256)
		: mCapacity(capacity)
		, mHistory(1, capacity)
		{
			channelCount.addObserver(mChannelCountObserver);
		}
		
		
		/** length of the delay
			TODO: dataspace integration for units other than samples
         */
		Parameter<int>	size = { this, "size", 1,
								[this]{
									for (auto& channel : mHistory)
										channel.resize((int)size);
								}
		};
		

		Message			clear = { "clear",
									Synopsis("Erase the delay history"),
									[this]{
										for (auto& channel : mHistory)
											channel.clear();
									}
		};
		

		Sample operator()(Sample x)
		{
			return (*this)(x, 0);
		}
		
		
		Sample operator()(Sample x, int channel)
		{
			mHistory[channel].resize(size+1); // need delay samples plus "now"
			mHistory[channel].write(x);
			return mHistory[channel].tail();
		}
		
		
		SharedSampleBundleGroup operator()(const SampleBundle& x)
		{
			auto out = adapt(x);
			
			for (int channel=0; channel < x.channelCount(); ++channel) {
				// write first (then read) so that we can acheive a zero-sample delay
				// mHistory[channel].write(x[channel]);
				// mHistory[channel].tail(out[0][channel]);
				
				// TODO: we can't acheive the above because we overwrite the memory before we read it!
				// TODO: the problem with the below is that we are limited to a minimum delay of one vector length.
				
				mHistory[channel].write(x[channel]);
				mHistory[channel].tail(out[0][channel]);
			}
			return out;
		}
		
	};
	

} // namespace Jamoma
