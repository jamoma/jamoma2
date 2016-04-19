/** @file
 
    @ingroup    jamoma2
 
    @breif      Extends SampleBundle to provide additional functions.
 
    @details    Defines a subclass of SampleBundle that adds functions for interpolation, padding, and waveshape generation.
 
    @author     Nathan Wolek, Timothy Place
    @copyright  Copyright (c) 2005-2016 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

*/

#pragma once


namespace Jamoma {
    
    /** Defines a subclass of SampleBundle that adds functions for interpolation, padding, and waveshape generation.
     These functions are typically used in applications such as oscillators, samplers, and grain playback.
     Keeping them separate from the core SampleBundle features ensures that these features are deployed only when necessary (such as dealing with audio recordings), instead of when they are not necessary (such as passing signal vectors between objects).
     */
    class SampleBuffer : public SampleBundle {
    public:
        static constexpr Classname classname = { "samplebuffer" };
        static constexpr auto tags = { "audio", "sample" };
        
        /** Create a SampleBuffer of a specific size.
         @param	channelCount	The number of channels for which to allocate memory.
         @param	frameCount		The number of samples per channel for which to allocate memory.
         */
        SampleBuffer(int channelCount, int frameCount) : SampleBundle(channelCount,frameCount)
        {
        }
        
        /** Default constructor creates a bundle containing a single sample. */
        SampleBuffer()
        : SampleBuffer(1,1)
        {}
        
        
        SampleBuffer(const SampleBuffer&) = default;	// inheriting the default copy constructor
        
    private:
        
    };
    
    
} // namespace Jamoma
