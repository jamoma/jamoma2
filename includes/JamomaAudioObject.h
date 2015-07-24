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
	
	
	class AdaptingSampleBundle : public SampleBundle {
		AudioObject*	mOwner;
		
	public:
		AdaptingSampleBundle(AudioObject* owner);
	};

	
	
	class AudioObject : public Object {
	public:
		
			/*
			Calculations should be done by overriding the () operator.
		 
			Audio operators can buffer their own output.
			While an optimization could be made to share the output buffers (like MSP does), it's not clear how that would be represented here.
			This seems somehow more declarative?
		 */
		SharedSampleBundle mOutput = std::make_shared<SampleBundle>();

		
		
		
		std::vector<AdaptingSampleBundle*>	mAdaptingSampleBundles;
		
		void registerAdaptingSampleBundle(AdaptingSampleBundle* asb)
		{
			mAdaptingSampleBundles.push_back(asb);
		}
		
		
		
		
		
		AudioObject() = default;
		
		
		Parameter<bool> bypass = {this, "bypass", false};

		
		Parameter<int>	channelCount = { this, "channelCount", 1,
			[this]{
				mOutput->resizeChannels(channelCount);
				
				// resize all AdaptingSampleVector instances for this class
				for (auto* asb : mAdaptingSampleBundles)
					asb->resizeChannels(channelCount);
			}
		};
		
		
		// used for initializing output to avoid resizing at perform time
		// also important for generator units
		Parameter<int>	frameCount = { this, "frameCount", 1,
									  [this]{ mOutput->resizeFrames(frameCount); }
		};
		
		
		Parameter<int>	sampleRate = { this, "sampleRate", 0 };
		
		
		virtual Sample operator()(const Sample x) = 0;
//		{
//			return 0.0;
//			return (*this)(x);
//		}

		
		virtual SharedSampleBundle operator()(const SampleBundle& x) = 0;
//		{
//			auto out = mOutput;
//			out->adapt(x);
//
//			for (int channel=0; channel<x.channelCount(); channel++)
//				std::transform(x[channel].begin(), x[channel].end(), out->at(channel).begin(), *this);
//
//			return out;
//		}
	public:
		virtual SharedSampleBundle operator()(const SharedSampleBundle& x) = 0;

		

	/*
		class SampleFunction {
		public:
			template <typename F>
			SampleFunction(F fn) {
				// TODO: store fn
			}
			
			Sample operator ()(Sample x) {
				return 0.0;
			}
		};
		
		
		
		
		class VectorFunction {
		public:
			template <class F>
			VectorFunction(F fn) {
//				mFn = fn;
			}
			
//			std::shared_ptr<SampleBundle> operator ()(const SampleBundle& x) {
//				std::shared_ptr<SampleBundle> y;
//				return y;
//			}
			

			
		private:
			//void* mFn;
		};
		
*/

	protected:
		
		
		
		
		
		/*
		 
			What do we really gain by making functor classes for the calc methods?
			If we want to switch perform operations then we either do a branch or an indirection -- so there is no performance benefit?
			Seems like simple methods are actually the most direct, inlinable, and understandable approach???
		 
			Maybe functors would be more reflexive
			For example to do code export or they could themselves be JIT compiled or overriden at runtime or ???
		 
		 SampleFunction	sampleCalc = { [this](const Sample x, int channel) -> Sample {
		 return x * gain;
		 }
		 };
		 
		 VectorFunction	vectorCalc = { [this](const SampleBundle& in) -> auto {
		 auto out = mOutput;
		 
		 for (int channel=0; channel<in.channelCount(); channel++)
		 std::transform(in[channel].begin(), in[channel].end(), out->at(channel).begin(), sampleCalc);
		 
		 return out;
		 }
		 };
		 
		 */
		
		
		
		
		
		static constexpr double kPi	= 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
		static constexpr double kTwoPi	= kPi * 2.0;
		
		// RADIANS CONVERSIONS: cannot make static because of access to a member data element
		// hz-to-radians conversion
		double hertzToRadians(const double hz)			// NOTE: Be sure to set the sr before calling this function
		{
			assert(sampleRate != 0);
			return(hz * kTwoPi / (double)sampleRate);
		}
		


		
	};
	
	
	
	
	
	
	double linearGainToDecibels(double input)
	{
		return input;
	}
	
	double decibelsToLinearGain(double input)
	{
		return input;
	}
	
	
	

	/** empty/default sampleBundle */
	static const SampleBundle kSampleBundleNone;
	static const SharedSampleBundle kSharedSampleBundleNone = {std::make_shared<SampleBundle>()};
	
	
	
	
	
	AdaptingSampleBundle::AdaptingSampleBundle(AudioObject* owner)
	: mOwner(owner)
	{
		mOwner->registerAdaptingSampleBundle(this);	// register with owner so we can get notifications
	}

	
}
