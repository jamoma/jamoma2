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
            testFillFunctions();
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
            
            /*  NW: this behavior was noticed while working on tests for Sync & logged as issue #63.
                It is caused by the return type of SharedSampleBundleGroup from our AudioObject.
                The SharedSampleBundleGroup is a shared_ptr, meaning the thing that it points to can and does change.
                This test has been preserved to demonstrate the expected behavior for future reference.
                If a stable set of samples are desired, your local return variable
                should explicitly specify a type of SampleBundle instead of using auto.
            */
            
            Jamoma::Sync my_sync16;
            
            my_sync16.channelCount = 1;
            my_sync16.frameCount = 16;
            
            my_sync16.sampleRate = 48000;
            my_sync16.phase = 0.0;
            my_sync16.frequency = 1.0;
            
            // process vector 1 and stash a value
            auto out_samples16_1 = my_sync16();
            
            Jamoma::Sample stash_value1 = out_samples16_1[0][0][0];
            
            // process vector 2 and stash a value
            auto out_samples16_2 = my_sync16();
            
            // grab same value from first vector, should be the same?
            Jamoma::Sample stash_value2 = out_samples16_1[0][0][0];
            
            // process vector 3 and stash a value
            auto out_samples16_3 = my_sync16();
            
            // grab same value from first vector, should be the same?
            Jamoma::Sample stash_value3 = out_samples16_1[0][0][0];
            
            // process vector 4 and stash a value
            auto out_samples16_4 = my_sync16();
            
            // grab same value from first vector, should be the same?
            Jamoma::Sample stash_value4 = out_samples16_1[0][0][0];
            
            // If you misunderstand what auto is doing, you may expect the following values to be equal.
            // However, because it is a shared pointer, the values are changing with each call to the operator.
            mTest->TEST_ASSERT("stashed value 1 = 2", mTest->compare(stash_value1, stash_value2, false));
            mTest->TEST_ASSERT("stashed value 1 = 3", mTest->compare(stash_value1, stash_value3, false));
            mTest->TEST_ASSERT("stashed value 1 = 4", mTest->compare(stash_value1, stash_value4, false));
            mTest->TEST_ASSERT("stashed value 2 = 3", mTest->compare(stash_value2, stash_value3, false));
            mTest->TEST_ASSERT("stashed value 2 = 4", mTest->compare(stash_value2, stash_value4, false));
            mTest->TEST_ASSERT("stashed value 3 = 4", mTest->compare(stash_value3, stash_value4, false));
            
        }
        
        void testFillFunctions() {
            
            Jamoma::SampleBundle	in_samples(2, 512);
            
            in_samples.fill_line();
            
            for(int i = 0; i < in_samples[0].size(); i++) {
                std::cout << "sample " << i << " = " << in_samples[0][i] << std::endl;
            }
            
        }
        
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::SampleBundleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
