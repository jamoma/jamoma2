/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Dcblocker class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"

namespace Jamoma {

	class SampleBundleTest {
		
		UnitTest<SampleBundleTest>*	mTest;
		
	public:
		SampleBundleTest(Jamoma::UnitTest<SampleBundleTest>* test)
		: mTest(test)
		{
			testBasic();
            testAutoCreatedSampleBundleGroup();
		}

		
		void testBasic()
		{
			Jamoma::Gain			my_gain;
			Jamoma::SampleBundle	in_samples(2, 8);
			
			my_gain.gain = 0.5;
			
			in_samples.fill(1.0);
			auto out_samples = my_gain(in_samples);
			
			my_gain.gain = 0.25;
			in_samples = out_samples;
			out_samples = my_gain(in_samples);
						
			auto bar = in_samples[0][0];
			mTest->TEST_ASSERT("in_sample casting operator", mTest->compare(bar, 0.5));
			
			in_samples[0][0] = 2.0;
			auto foo = in_samples[0][0];
			mTest->TEST_ASSERT("setting and getting", mTest->compare(foo, 2.0));
		}
        
        void testAutoCreatedSampleBundleGroup() {
            
            // NW: this behavoir was noticed while working on tests for Phasor
            // it appears that sample values in first auto created vector change
            // as each subseqent vector is processed
            
            Jamoma::Phasor my_phasor16;
            
            my_phasor16.channelCount = 1;
            my_phasor16.frameCount = 16;
            
            my_phasor16.sampleRate = 48000;
            my_phasor16.phase = 0.0;
            my_phasor16.frequency = 1.0;
            
            // process vector 1 and stash a value
            auto out_samples16_1 = my_phasor16();
            
            Jamoma::Sample stash_value1 = out_samples16_1[0][0][0];
            
            // process vector 2 and stash a value
            auto out_samples16_2 = my_phasor16();
            
            // grab same value from first vector, should be the same?
            Jamoma::Sample stash_value2 = out_samples16_1[0][0][0];
            
            // process vector 3 and stash a value
            auto out_samples16_3 = my_phasor16();
            
            // grab same value from first vector, should be the same?
            Jamoma::Sample stash_value3 = out_samples16_1[0][0][0];
            
            // process vector 4 and stash a value
            auto out_samples16_4 = my_phasor16();
            
            // grab same value from first vector, should be the same?
            Jamoma::Sample stash_value4 = out_samples16_1[0][0][0];
            
            // I would expect all these to be equal, but they are NOT
            // Maybe I misunderstand what auto does?
            // But it is also possible auto is creating wrong type (i.e. not ImmutableSampleBundleGroup)
            // Let's be sure.
            mTest->TEST_ASSERT("stashed value 1 = 2", mTest->compare(stash_value1, stash_value2));
            mTest->TEST_ASSERT("stashed value 1 = 3", mTest->compare(stash_value1, stash_value3));
            mTest->TEST_ASSERT("stashed value 1 = 4", mTest->compare(stash_value1, stash_value4));
            mTest->TEST_ASSERT("stashed value 2 = 3", mTest->compare(stash_value2, stash_value3));
            mTest->TEST_ASSERT("stashed value 2 = 4", mTest->compare(stash_value2, stash_value4));
            mTest->TEST_ASSERT("stashed value 3 = 4", mTest->compare(stash_value3, stash_value4));
            
        }
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::SampleBundleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
