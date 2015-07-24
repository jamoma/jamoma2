//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

#pragma once


namespace Jamoma {


	using Sample = double;
	using SampleVector = std::vector<Sample>;

	class SampleBundle;
	using SharedSampleBundle = std::shared_ptr<SampleBundle>;
	using ImmutableSampleBundle = const SampleBundle;
	using SharedImmutableSampleBundle = std::shared_ptr<ImmutableSampleBundle>;

	/**	SampleBundle is a container of N vectors of audio each of size M, where N is the number of channels and M is the vector length.

		Internally this is represented as a vector of vectors (as opposed to representation as a matrix).
		In many cases this is an advantage:
		-	almost all of the time we iterate channels as an outer loop and samples as an inner loop
			therefore for those majority of the times we want to the compactness of channels being together, not interleaved.
		-	we additionally get samples uninterleaved from many host environments (Max, Pd, VST, etc)
	 
		In cases where the representation could be interleaved 
		(e.g. an FFT where the real and imaginary might be 'channels')
		we likely want to use a different matrix type anyway.
	 
		Special care should be considered for instances of const SampleBundle (a.k.a. ImmutableSampleBundle).
		This case is used as audio playback buffer for classes such as wavetable oscillators and grain players.
		In this case content can only be set at construction.
	 */
	class SampleBundle {

		using SampleBundleData = std::vector<SampleVector>;
		
	public:
		SampleBundle(int channelCount, int frameCount)
		{
			mFrameCount = frameCount;
			mChannels.resize(channelCount);
			for (auto& channel : mChannels)
				channel.resize(mFrameCount);
		}
		
		SampleBundle()
		: SampleBundle(1,1)
		{}
		
		
		
		// SampleWad(const SampleWad& otherSampleWad)
		// {}
		
		// For convenience -- especially multichannel
		// Can edit and shape the samples as a SampleBundle
		// Then copy or *move* it into a Wad
		// SampleWad(const SampleBundle& otherSampleWad)
		// {}
		

		
		size_t channelCount() const { return mChannels.size(); }
		size_t frameCount() const { return mFrameCount; }
		
		
		
		SampleVector& at(size_t index)
		{
			return mChannels[index];
		}
		
		const SampleVector& at(size_t index) const
		{
			return mChannels[index];
		}

		
		SampleVector& operator[](size_t index)
		{
			SampleVector& temp = mChannels[index];
			return temp;
		}
		
		const SampleVector& operator[](size_t index) const
		{
			return const_cast<SampleBundle*>(this)->mChannels[index];
		}
		
		/**************/
		// Methods for non-const instances only!
		
		void resizeChannels(size_t channelCount)
		{
			mChannels.resize(channelCount);
			for (auto& channel : mChannels)
				channel.resize(mFrameCount);
		}
		
		void resizeFrames(size_t frameCount)
		{
			mFrameCount = frameCount;
			for (auto& channel : mChannels)
				channel.resize(mFrameCount);
		}
		
		void adapt(const SampleBundle& other)
		{
			resizeChannels(other.channelCount());
			resizeFrames(other.frameCount());
		}
		
		void fill(Sample value)
		{
			for (auto& channel : mChannels)
				std::fill(channel.begin(), channel.end(), value);
		}
		
		/* perhaps the following would be better as an "apply" method or something?
		 template <class T>
		 void operator()(SharedSampleBundle& out, T target) const
		 {
			for (int channel=0; channel<channelCount(); channel++)
		 std::transform( (*this)[channel].begin() , (*this)[channel].end() , out->at(channel).begin() , target);
		 }
		 */
		
		/*****************/

		
		SampleBundleData::const_iterator cbegin() const
		{ return mChannels.cbegin(); }
		SampleBundleData::const_iterator cend() const
		{ return mChannels.cend(); }
		SampleBundleData::const_iterator begin() const
		{ return mChannels.begin(); }
		SampleBundleData::const_iterator end() const
		{ return mChannels.end(); }
		

		
	protected:
		SampleBundleData	mChannels;
		size_t			mFrameCount;
	};

	
	
	
	
	
	
	
	
	
	
	
	class SampleBundleGroup {
	
	};

	using SharedSampleBundleGroup = std::shared_ptr<SampleBundleGroup>;

	
	
	
	
}
