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
    class Oscillator : public AudioObject {
    public:
        static constexpr Classname classname = { "oscillator" };
        static constexpr auto tags = { "dspGeneratorLib", "audio", "generator", "oscillator", "wavetable" };
        
        /** Table size is fixed at instantiation
         */
        Oscillator(std::size_t tableSize = 8192)
        : mLookupTable(1, tableSize)
        {
            mLookupTable.generate(); // fill with sine as default
            // NW: Do we need observers here?
        }
        
        Parameter<double, Limit::Wrap<double>, NativeUnit::None<double>>	phase		= { this,
            "phase",
            0.0,
            Range<double>(0.0, 1.0),
            Setter([this]{
                mSync.phase = phase;
            }),
            Synopsis("Initial phase of the periodic waveform")
        };
        
        // NW: These range and limit constraints are being applied here AND within the mSync. Should we remove this one?
        Parameter<double, Limit::Fold<double>, NativeUnit::None<double>>	frequency	= {	this,
            "frequency",
            1.0,
            Range<double>(sampleRate * -0.5, sampleRate * 0.5),
            Setter( [this]{
                mSync.frequency = frequency;
            } ),
            Synopsis("Rate at which the waveform should cycle")
        };
        
        /** Process one sample.
         @param x   Sample to be processed. Unused.
         @return    Processed sample.
         */
        Sample operator()(Sample x)
        {
			Sample oneSample = mSync(0.0);
            return mLookupTable[0].at(oneSample);
        }
        
        /** Process a SharedSampleBundleGroup.
         @param	x	SharedSampleBundleGroup to be processed.
         @return		Processed SharedSampleBundleGroup.
         */
        SharedSampleBundleGroup operator()(const SampleBundle& x = kSampleBundleNone)
        {
            auto out = mOutput;
            
            // Do something here
            
            return out;
        }
        
    private:
        Jamoma::Sync                mSync;
        Jamoma::SampleBundle        mLookupTable;
    };

} // namespace Jamoma