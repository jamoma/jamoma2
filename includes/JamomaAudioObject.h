//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

#pragma once

#include "JamomaObject.h"
#include "JamomaSample.h"


namespace Jamoma {

	
	class AudioObject;
	
	
	/**	The AdaptingSampleBundle is a SampleBundle that automatically resizes its number of channels 
		when the channelCount parameter of the owning AudioObject changes.	*/
	class AdaptingSampleBundle : public SampleBundle {
		AudioObject*	mOwner;

	public:
		
		/** Must pass a pointer to the owning object, i.e. "this", so that this object can register for notifications.
			@param	AudioObject's "this" pointer
		 */
		AdaptingSampleBundle(AudioObject* owner);
	};

	
	/**	The base class for objects that serve as audio unit generators.
		Calculations are done by overriding the () operator for individual samples or bundles of samples.
		Each AudioObject provides SharedSampleBundleGroup to buffer it's own output.
	 */
	class AudioObject : public Object {
	protected:
		
		/**	Each AudioObject provides SharedSampleBundleGroup to buffer it's own output.
			Before you use this you should make a local copy to ensure that the reference count doesn't go to zero while you are writing your output.
			A copy of a SharedSampleBundleGroup is a copy of a shared pointer, not a copy of the data in the bundle group.
		 */
		SharedSampleBundleGroup mOutput;

		
	private:
		friend class AdaptingSampleBundle;
		
		/** We maintain a list of AdaptingSampleBundles so that we can notify them when the channelCount parameter changes */
		std::vector<AdaptingSampleBundle*>	mAdaptingSampleBundles;
		
		/** Called internally by the AdaptingSampleBundle constructor to register the bundle for notifications. */
		void registerAdaptingSampleBundle(AdaptingSampleBundle* asb)
		{
			mAdaptingSampleBundles.push_back(asb);
		}
		
		
	public:
		
		/** Default constructor. */
		AudioObject() = default;
		
		
		/** The channelCount parameter is universal to all AudioObjects.
			It is used by any AdaptingSampleBundles and also for generators that don't take an input signal.
			TODO: should get an intelligent default from the graph that owns this object (if there is a one)
		 */
		Parameter<int>	channelCount = { this, "channelCount", 1,
			[this]{
				mOutput.resizeChannels(channelCount);
				
				// resize all AdaptingSampleVector instances for this class
				for (auto* asb : mAdaptingSampleBundles)
					asb->resizeChannels(channelCount);
			}
		};
		
		
		/** The frameCount parameter is used for initializing output to avoid resizing at perform time.
			It is also important for generator units that don't take an input AudioBundle.
			TODO: should get an intelligent default from the graph that owns this object (if there is a one)
		 */
		Parameter<int>	frameCount = { this, "frameCount", 1,
									  [this]{ mOutput.resizeFrames(frameCount); }
		};
		
		
		/** The sampleRate parameter may not be used in all cases, but provides a standard interface for when it is needed.
			TODO: need to deliver notifications, e.g. to recalculate filter coefficients in subclasses
			TODO: should get an intelligent default from the graph that owns this object (if there is a one)
		 */
		Parameter<int>	sampleRate = { this, "sampleRate", 0 };
		
		
		/** Calculate a single sample.
			Subclasses must override this.
			This is typically where the meet of your algorithm will be defined.
			@param	x	An input sample
			@return		An output sample
		 */
		virtual Sample operator()(const Sample x) = 0;

		
		/** Calculate a bundle of samples.
			Subclasses must override this.
			Typically the logistics of getting the required samples for the channels and vectors will happen in this function and then be handed-off 
			to the above single-sample function (which can be inlined by the compiler).
			Output should be buffered (written) to mOutput, and then mOutput returned from this method.
			@param	x	An input bundle
			@return		This classes' output bundle group
		 */
		virtual SharedSampleBundleGroup operator()(const SampleBundle& x) = 0;

	
		/** Calculate an entire SampleBundleGroup.
			Only classes that need to accept multiple SampleBundles for input (e.g. a crossfader or IFFT operator) will need to override this method.
			The default provided here will suffice for most subclasses.
			@param	x	An input bundle
			@return		This classes' output bundle group
		 */
		virtual SharedSampleBundleGroup operator()(const SharedSampleBundleGroup x)
		{
			return (*this)(x[0]);
		}
		
		
		/** Convience method for doing Hertz-to-radians conversion based upon the current sampleRate 
			@param	hz	The input in hertz.
			@return		The output in radians.
		 */
		double hertzToRadians(const double hz)
		{
			assert(sampleRate != 0);
			return(hz * kTwoPi / (double)sampleRate);
		}
	};
	
	
#pragma mark -
#pragma mark Implementation of AdaptingSampleBundle
	
	inline AdaptingSampleBundle::AdaptingSampleBundle(AudioObject* owner)
	: mOwner(owner)
	{
		mOwner->registerAdaptingSampleBundle(this);	// register with owner so we can get notifications
	}

	
#pragma mark -
#pragma mark Utilities that likely belong elsewhere


	/** Convert linear amplitude into decibels.
		@param	input	The linear gain value to convert.
		@return			Converted decibel value.
	 */
	inline double linearGainToDecibels(double input)
	{
		if (input < 0.0)
			return 0.0;
		else
			return(20.0 * (log10(input)));
	}

	/** Convert decibels into linear ampliude.
		@param	input	The decibel value to convert.
		@return			The converted linear gain value.
	 */
	inline double decibelsToLinearGain(double input)
	{
		return(pow(10.0, (input / 20.0)));
	}


} // namespace Jamoma
