/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Delay line implementations
	
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

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
				mHistory[channel].write(x[channel]);
				mHistory[channel].tail(out[0][channel]);
			}
			return out;
		}
		
	};
    
    /**	A multichannel interpolating delay line.
     @warning This class is experimental. May be eventually be replaced with template design in Delay class.
     */
    class DelayWithLinearInterpolation : public AudioObject {
        
        const std::size_t			mCapacity;
        CircularSampleBufferGroup	mHistory;
        std::size_t                 mIntegralDelay;
        double                      mFractionalDelay;
        double                      mOneMinusFractionalDelay;
        
        
        // NW: removing Observer temporarily
        
    public:
        static constexpr Classname classname = { "delayWithLinearInterpolation" };
        static constexpr auto tags = { "dspEffectsLib", "audio", "processor", "delay" };
        
        
        /** Capacity of the delay is fixed at instantiation
         */
        DelayWithLinearInterpolation(std::size_t capacity = 256)
        : mCapacity(capacity)
        , mHistory(1, capacity)
        {
            // NW: see above removal of Observer
            //channelCount.addObserver(mChannelCountObserver);
        }
        
        
        /** length of the delay
         TODO: dataspace integration for units other than samples
         */
        Parameter<double>	size = { this, "size", 1.0,
            [this]{
                mIntegralDelay = (int)size;
                mFractionalDelay = size - mIntegralDelay;
                mOneMinusFractionalDelay = 1.0 - mFractionalDelay;
                
                for (auto& channel : mHistory)
                    channel.resize(mIntegralDelay+1);
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
                mHistory[channel].write(x[channel]);
                mHistory[channel].tail(out[0][channel]);
            }
            return out;
        }
        
        std::size_t integralDelay() {
            return mIntegralDelay;
        }
        
        double fractionalDelay() {
            return mFractionalDelay;
        }
        
        double oneMinusFractionalDelay() {
            return mOneMinusFractionalDelay;
        }
        
        
    };
	

} // namespace Jamoma
