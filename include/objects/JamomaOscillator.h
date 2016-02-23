/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generate a basic, periodic waveform using an internal lookup table.
	
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"
#include "JamomaSync.h"


namespace Jamoma {
    
    /**	This AudioObject generates a <a href="https://en.wikipedia.org/wiki/Waveform">periodic waveform</a> by filling an internal SampleBundle with the shape to be repeated at a given frequency.
     This method of sound generation is typically referred to as <a href="https://en.wikipedia.org/wiki/Table-lookup_synthesis">table-lookup</a> or <a href="https://en.wikipedia.org/wiki/Wavetable_synthesis">wavetable</a> synthesis.
     */
    class Oscillator : public Sync {
    public:
        static constexpr Classname classname = { "oscillator" };
        static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "oscillator", "wavetable" };
        
        /** Table size is fixed at instantiation
         */
        Oscillator(std::size_t tableSize = 8192)
        : mLookupTable(1, tableSize)
        {
            syncFinalValue = tableSize; // ramp from 0 to tableSize
            mLookupTable.generate();
            mLookupTable.applySamplePadding(2);
        }
        
        Parameter<double, Limit::None<double>, NativeUnit::LinearGain>		gain = { this, "gain", 1.0 };		///< scaling applied to the output
        
        // NW: should we provide a way to get the current phase?
        
        /** Process one sample.
         @param x   Sample to be processed. Unused.
         @return    Processed sample.
         */
        Sample operator()(Sample x)
        {
            // call operator() from parent Sync class
            double oneSample = Sync::operator()(0.0);
            // add in padding
            oneSample += mLookupTable.paddingSize();
            // perform additional lookup
            return gain * mLookupTable.at(oneSample);
        }
        
        /** Process a SharedSampleBundleGroup.
         @param	x	SharedSampleBundleGroup to be processed.
         @return		Processed SharedSampleBundleGroup.
         */
        SharedSampleBundleGroup operator()(const SampleBundle& x = kSampleBundleNone)
        {
            auto out = mOutput;
            
            for (int channel=0; channel<x.channelCount(); ++channel)
                for	(auto& sample : out[0][channel])
                    sample = (*this)(0.0);
            
            return out;
        }
        
    private:
        Jamoma::SampleBundle        mLookupTable;
        
        
    };

} // namespace Jamoma