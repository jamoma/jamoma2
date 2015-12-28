/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Store samples in a chunk of memory.
	
	@details 	Defines the Sample datatype and several layers of containers for representing the relationship between Samples in memory. 
				These containers in order from lowest to highest level are referred to as Sample, SampleVector, SampleBundle, and SampleBundleGroup.
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {


	using Sample = double;
	using SampleVector = std::vector<Sample>;

	
#pragma mark -
#pragma mark Sample Bundles

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
		
		SampleBundleData	mChannels;		// each item in this vector represents a channel, which itself is a vector of samples
		size_t				mFrameCount;	// if we change the number of channels we could loose the framecount in the vectors contained by mChannels, so we cache it here.

	public:
		/** Create a SampleBundle of a specific size.
			@param	channelCount	The number of channels for which to allocate memory.
			@param	frameCount		The number of samples per channel for which to allocate memory.
		 */
		SampleBundle(int channelCount, int frameCount)
		{
			mFrameCount = frameCount;
			mChannels.resize(channelCount);
			for (auto& channel : mChannels)
				channel.resize(mFrameCount);
		}
		
		/** Default constructor creates a bundle containing a single sample. */
		SampleBundle()
		: SampleBundle(1,1)
		{}
		
	
		SampleBundle(const SampleBundle&) = default;	// inheriting the default copy constructor
		
		
		// TODO: consider the design of this class and the ways that it is used for assessment of the move operator
		// For the moment we will implicitly use the default -- explicitly using the default will delete the copy-assignment operator, which we don't want.
		// SampleBundle(SampleBundle&&) = default;

		
		/**	Return the number of channels represented in the bundle.
			@return	The number of channels.
		 */
		size_t channelCount() const
		{
			return mChannels.size();
		}

		
		/**	Return the number of frames represented in the bundle.
			@return	The number of frames.
		 */
		size_t frameCount() const
		{
			return mFrameCount;
		}
		
		
		/**	Access the vector at the specified channel in the bundle.
			@param	channel		The channel whose vector you wish to access.
			@return				A reference to the channel's vector.
		 */
		SampleVector& operator[](size_t channel)
		{
			SampleVector& temp = mChannels[channel];
			return temp;
		}
		
		
		/**	Access the vector at the specified channel in the bundle.
			@param	channel		The channel whose vector you wish to access.
			@return				A reference to the channel's vector.
		 */
		const SampleVector& operator[](size_t index) const
		{
			return const_cast<SampleBundle*>(this)->mChannels[index];
		}
		
		
		/**	Change the channel count of the bundle.
			@param	channelCount	The new number of channels to be contained by the bundle.
		 */
		void resizeChannels(size_t channelCount)
		{
			mChannels.resize(channelCount);
			for (auto& channel : mChannels)
				channel.resize(mFrameCount);
		}
		
		/**	Change the frame count for the bundle.
			@param	frameCount	The new number of frames to be contained by the bundle.
		 */
		void resizeFrames(size_t frameCount)
		{
			mFrameCount = frameCount;
			for (auto& channel : mChannels)
				channel.resize(mFrameCount);
		}
		
		
		/**	Change the size (both channelCount and frameCount) for the bundles to match that of a reference bundle.
			@param	other	A bundle whose dimensions should be used as a model for the dimensions of this bundle.
		 */
		void adapt(const SampleBundle& other)
		{
			resizeChannels(other.channelCount());
			resizeFrames(other.frameCount());
		}
		
		
		/**	Set the values of all samples to a constant.  
			If no argument is provided all samples will be set to zero.
			@param	value	A scalar value to be assigned to all samples in the bundle.
		 */
		void fill(Sample value = 0)
		{
			for (auto& channel : mChannels)
				std::fill(channel.begin(), channel.end(), value);
		}
		
		
		// TODO: Add some additional fill() options -- e.g. filling with a sine function, sinc function, etc.
        // These can emulate options found here:
        // https://github.com/jamoma/JamomaCore/blob/master/DSP/library/source/TTSampleMatrix.cpp#L254
        
        void fill_line()
        {
            class LineGen {
            private:
                int current;
                int max;
            public:
                LineGen (int size = 1) : max(size){
                    current=-1;
                }
                Sample operator()() {
                    return (Sample)++current / max;
                }
            };
            
            for (auto& channel : mChannels)
                std::generate(channel.begin(), channel.end(), LineGen(frameCount()));
        }
		
		
		/** Copy values into the SampleBundle from outside. 
			@param	channel		The channel to which the samples should be copied.
			@param	frameCount	The number of samples to be copied.
			@param	values		A pointer to the first value to be copied.
		 */
		template <typename T>
		void copyIn(int channel, int frameCount, T* values)
		{
			assert(frameCount == this->frameCount());
				   
			SampleVector& vector = (*this)[channel];

			for (int i=0; i<frameCount; ++i)
				vector[i] = values[i];
		}
		
		
		/** Copy values out of the SampleBundle to an outside sink.
			@param	channel		The channel from which the samples should be copied.
			@param	frameCount	The number of samples to be copied.
			@param	values		A pointer to the first destination at which the samples will be copied.
		 */
		template <typename T>
		void copyOut(int channel, int frameCount, T* values)
		{
			assert(frameCount == this->frameCount());
			
			SampleVector& vector = (*this)[channel];
			
			for (int i=0; i<frameCount; ++i)
				values[i] = vector[i];
		}
		

		// TODO: add an "apply" method to which is passed a std::function which then performs a transformation on the bundle contents.
		// perhaps there would be a couple of variations:
		// 1. a per-sample type transformation (e.g. scaling) using std::transform
		// 2. a channel-long transform like applying a hamming window
		// 3. something that needs data from all channels such as a normalize function
		

		// Iterators to allow us to use STL algorithms and such directly on the SampleBundle

		SampleBundleData::const_iterator cbegin() const
		{ return mChannels.cbegin(); }
		SampleBundleData::const_iterator cend() const
		{ return mChannels.cend(); }
		SampleBundleData::const_iterator begin() const
		{ return mChannels.begin(); }
		SampleBundleData::const_iterator end() const
		{ return mChannels.end(); }
	};


	/**	An ImmutableSampleBundle is the preferred way to represent what might be referred to traditionally as "buffers" in environments like Max.
		In this case we have a bundle which must be fully initialized at construction and is then read-only from that point on.
		If you wish to have a buffer with different content then you create a new ImmutableSampleBundle and dispose of the old one.
		To ensure that no one is still using an ImmutableSampleBundle before it is deleted, it is recommended to use a SharedImmutableSampleBundle.
	 */
	using ImmutableSampleBundle = const SampleBundle;
	
	
	/**	The SharedImmutableSampleBundle adds reference counting and life-cycle management to the ImmutableSampleBundle.
	 */
	class SharedImmutableSampleBundle {
		std::shared_ptr<ImmutableSampleBundle> mSampleBundle = std::make_shared<ImmutableSampleBundle>();
	public:
		SharedImmutableSampleBundle() = default;
		
		/** Access the ImmutableSampleBundle
			@return		A reference to the bundle.
		 */
		operator ImmutableSampleBundle&() const
		{
			return *mSampleBundle;
		}
	};
	
	
#pragma mark -
#pragma mark Sample Bundle Groups
	
	
	/**	A Group of SampleBundles.
		Typically you will want to use SharedSampleBundleGroup instead of using this class directly because it is reference counted.
	 */
	class SampleBundleGroup {
		friend class SharedSampleBundleGroup;
		using SampleBundleGroupData = std::vector<SampleBundle>;
		
		SampleBundleGroupData	mSampleBundles{1}; // initialized to contain 1 SampleBundle
		
	public:
		SampleBundleGroup() = default;
	};

	
	/** A reference counted SampleBundleGroup. 
		This permits a group of SampleBundles to be passed together for both input and output from e.g. audio vector perform routines. */
	class SharedSampleBundleGroup {
		std::shared_ptr<SampleBundleGroup> mBundleGroup = std::make_shared<SampleBundleGroup>();

	public:
		SharedSampleBundleGroup() = default;
		
		
		/**	Get the channel count for a given bundle in the bundle group.
			By default it returns the channel count for the first bundle.
			@param	bundle	The index of the bundle to query.
			@return			The number of channels in the specified SampleBundle.
		 */
		size_t channelCount(int bundle = 0) const
		{
			return mBundleGroup->mSampleBundles[0].channelCount();
		}

		
		/**	Get the frame count for a given bundle in the bundle group.
			By default it returns the frame count for the first bundle.
			@param	bundle	The index of the bundle to query.
			@return			The number of frames in the specified SampleBundle.
		 */
		size_t frameCount(int bundle = 0) const
		{
			return mBundleGroup->mSampleBundles[0].frameCount();
		}

		
		/**	Change the channel count for all bundles in the bundle group.
			@param	channelCount	The new number of channels to be contained by the bundles.
		 */
		void resizeChannels(size_t channelCount)
		{
			for (auto& bundle : mBundleGroup->mSampleBundles)
				bundle.resizeChannels(channelCount);
		}

		
		/**	Change the frame count for all bundles in the bundle group.
			@param	frameCount	The new number of frames to be contained by the bundles.
		 */
		void resizeFrames(size_t frameCount)
		{
			for (auto& bundle : mBundleGroup->mSampleBundles)
				bundle.resizeFrames(frameCount);
		}
		
		
		/**	Change the size (both channelCount and frameCount) for all bundles to match that of a reference bundle.
			@param	other	A bundle whose dimensions should be used as a model for the dimensions of the bundles in the group.
		 */
		void adapt(const SampleBundle& other)
		{
			resizeChannels(other.channelCount());
			resizeFrames(other.frameCount());
		}

	
		/**	Access a given bundle in the bundle group.
			@param	index	The bundle to access.
			@return			A reference to the bundle.
		 */
		SampleBundle& operator[](size_t index) const
		{
			SampleBundle& temp = mBundleGroup->mSampleBundles[index];
			return temp;
		}

		
		/** Casting to a SampleBundle will fetch a reference to the first bundle in the group. 
			@return		A reference to the first bundle.
		 */
		operator SampleBundle&() const
		{
			return mBundleGroup->mSampleBundles[0];
		}
		
	};


	/** Instance of an empty/default sampleBundle for use as a default function parameter. */
	static const SampleBundle kSampleBundleNone;

	
} // namespace Jamoma
