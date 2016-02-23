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
            //printInterpolationDifferences();
            testInterpolationAtWholeNumbers();
            testZeroPadding();
            testSamplePadding();
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
            my_sync16.initialphase = 0.0;
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
        
        void printInterpolationDifferences() {
            SampleBundle test_bundle(2,64);
            
            test_bundle.generate<Generator::UnipolarRamp<Sample>>();
            
            Jamoma::Sample temp;
            for (int i = 0; i < 85; i ++)
            {
                double d = 3.0 * i / 4.0;
                
                temp = test_bundle.at<Jamoma::Interpolator::None<Sample>>(d);
                std::cout << "none    ( " << d << " ) = " << temp << std::endl;
                
                temp = test_bundle.at<Jamoma::Interpolator::Nearest<Sample>>(d);
                std::cout << "nearest ( " << d << " ) = " << temp << std::endl;
                
                temp = test_bundle.at<Jamoma::Interpolator::Cosine<Sample>>(d);
                std::cout << "cosine  ( " << d << " ) = " << temp << std::endl;
                
                temp = test_bundle.at<Jamoma::Interpolator::Linear<Sample>>(d);
                std::cout << "linear  ( " << d << " ) = " << temp << std::endl;
                
                temp = test_bundle.at<Jamoma::Interpolator::Cubic<Sample>>(d);
                std::cout << "cubic   ( " << d << " ) = " << temp << std::endl;
                
                temp = test_bundle.at<Jamoma::Interpolator::Spline<Sample>>(d);
                std::cout << "spline   ( " << d << " ) = " << temp << std::endl;
                
                std::cout << "***" << std::endl;
                
            }
            
        }
        
        void testInterpolationAtWholeNumbers() {
            int		badSampleCountCosine = 0;
            int		badSampleCountLinear = 0;
            int		badSampleCountCubic = 0;
            int		badSampleCountSpline = 0;
            SampleBundle test_bundle(2,64);
            
            test_bundle.generate<Generator::UnipolarRamp<Sample>>();
            
            Jamoma::Sample tempCosine;
            Jamoma::Sample tempLinear;
            Jamoma::Sample tempCubic;
            Jamoma::Sample tempSpline;
            Jamoma::Sample tempExpected;
            for (int i = 0; i < 85; i ++)
            {
                double d = 3.0 * i / 4.0;
                
                tempCosine = test_bundle.at<Jamoma::Interpolator::Cosine<Sample>>(d);
                tempLinear = test_bundle.at<Jamoma::Interpolator::Linear<Sample>>(d);
                tempCubic = test_bundle.at<Jamoma::Interpolator::Cubic<Sample>>(d);
                tempSpline = test_bundle.at<Jamoma::Interpolator::Spline<Sample>>(d);
                
                if (i % 4 == 0) { // every 4th item should be a whole number we can compare with regular access
                    tempExpected = test_bundle[0][int(d)];
                    if (tempCosine != tempExpected) badSampleCountCosine++;
                    if (tempLinear != tempExpected) badSampleCountLinear++;
                    if (tempCubic != tempExpected) badSampleCountCubic++;
                    if (tempSpline != tempExpected) badSampleCountSpline++;
                }
                
            }
            
            mTest->TEST_ASSERT("cosine interpolation produces same values as [] operator", badSampleCountCosine == 0);
            mTest->TEST_ASSERT("linear interpolation produces same values as [] operator", badSampleCountLinear == 0);
            mTest->TEST_ASSERT("cubic interpolation produces same values as [] operator", badSampleCountCubic == 0);
            mTest->TEST_ASSERT("spline interpolation produces same values as [] operator", badSampleCountSpline == 0);
            
        }
        
        
        void testZeroPadding() {
            SampleBundle paddedBundle(1,64);
            paddedBundle.generate<Generator::Cosine<Sample>>();
            
            mTest->TEST_ASSERT("cosine starts with non-zero before padding", paddedBundle[0][0] != 0.0);
            mTest->TEST_ASSERT("cosine ends with non-zero before padding", paddedBundle[0][63] != 0.0);
            
            paddedBundle.applyZeroPadding(2);
            
            size_t tempFrameCount = paddedBundle.frameCount();
            
            mTest->TEST_ASSERT("bundle reports proper frameCount after padding", tempFrameCount == 68);
            
            size_t tempPaddingSize = paddedBundle.paddingSize();
            
            mTest->TEST_ASSERT("bundle reports proper paddingSize after padding", tempPaddingSize == 2);
            
            int badSampleCount = 0;
            
            if (paddedBundle[0][0] != 0.0) badSampleCount++;
            if (paddedBundle[0][1] != 0.0) badSampleCount++;
            if (paddedBundle[0][2] == 0.0) badSampleCount++;
            if (paddedBundle[0][3] == 0.0) badSampleCount++;
            if (paddedBundle[0][64] == 0.0) badSampleCount++;
            if (paddedBundle[0][65] == 0.0) badSampleCount++;
            if (paddedBundle[0][66] != 0.0) badSampleCount++;
            if (paddedBundle[0][67] != 0.0) badSampleCount++;
            
            mTest->TEST_ASSERT("bundle applied zero padding successfully", badSampleCount == 0);
            
        }
        
        void testSamplePadding() {
            SampleBundle paddedBundle(2,64);
            paddedBundle.generate<Generator::UnipolarRamp<Sample>>();
            
            paddedBundle.applySamplePadding(3);
            
            size_t tempFrameCount = paddedBundle.frameCount();
            
            mTest->TEST_ASSERT("bundle reports proper frameCount after padding", tempFrameCount == 70);
            
            size_t tempPaddingSize = paddedBundle.paddingSize();
            
            mTest->TEST_ASSERT("bundle reports proper paddingSize after padding", tempPaddingSize == 3);
            
            int badSampleCount = 0;
            
            // channel 0
            if (paddedBundle[0][0] != paddedBundle[0][64]) badSampleCount++;
            if (paddedBundle[0][1] != paddedBundle[0][65]) badSampleCount++;
            if (paddedBundle[0][2] != paddedBundle[0][66]) badSampleCount++;
            if (paddedBundle[0][3] != paddedBundle[0][67]) badSampleCount++;
            if (paddedBundle[0][4] != paddedBundle[0][68]) badSampleCount++;
            if (paddedBundle[0][5] != paddedBundle[0][69]) badSampleCount++;
            
            // channel 1
            if (paddedBundle[1][0] != paddedBundle[1][64]) badSampleCount++;
            if (paddedBundle[1][1] != paddedBundle[1][65]) badSampleCount++;
            if (paddedBundle[1][2] != paddedBundle[1][66]) badSampleCount++;
            if (paddedBundle[1][3] != paddedBundle[1][67]) badSampleCount++;
            if (paddedBundle[1][4] != paddedBundle[1][68]) badSampleCount++;
            if (paddedBundle[1][5] != paddedBundle[1][69]) badSampleCount++;
            
            
            mTest->TEST_ASSERT("bundle applied sample padding successfully", badSampleCount == 0);
            
            
        }

		
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::SampleBundleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
