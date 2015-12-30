/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for Generator classes
 
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class GeneratorTest {
	
	Jamoma::UnitTest<GeneratorTest>*	mTest;
	
public:
	GeneratorTest(Jamoma::UnitTest<GeneratorTest>* test)
	: mTest(test)
	{
        testRamp();
        testUnipolarRamp();
        testSine();
        testTriangle();
        testConsistentAcrossMultipleChannels();
	}
    
    void testRamp() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::Ramp<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputRamp = {
            -1,
            -0.96875,
            -0.9375,
            -0.90625,
            -0.875,
            -0.84375,
            -0.8125,
            -0.78125,
            -0.75,
            -0.71875,
            -0.6875,
            -0.65625,
            -0.625,
            -0.59375,
            -0.5625,
            -0.53125,
            -0.5,
            -0.46875,
            -0.4375,
            -0.40625,
            -0.375,
            -0.34375,
            -0.3125,
            -0.28125,
            -0.25,
            -0.21875,
            -0.1875,
            -0.15625,
            -0.125,
            -0.09375,
            -0.0625,
            -0.03125,
            0,
            0.03125,
            0.0625,
            0.09375,
            0.125,
            0.15625,
            0.1875,
            0.21875,
            0.25,
            0.28125,
            0.3125,
            0.34375,
            0.375,
            0.40625,
            0.4375,
            0.46875,
            0.5,
            0.53125,
            0.5625,
            0.59375,
            0.625,
            0.65625,
            0.6875,
            0.71875,
            0.75,
            0.78125,
            0.8125,
            0.84375,
            0.875,
            0.90625,
            0.9375,
            0.96875
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputRamp.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputRamp[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testRamp generated correct output", badSampleCount == 0);
        
    }
    
    void testUnipolarRamp() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::UnipolarRamp<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputUnipolarRamp = {
            0,
            0.015625,
            0.03125,
            0.046875,
            0.0625,
            0.078125,
            0.09375,
            0.109375,
            0.125,
            0.140625,
            0.15625,
            0.171875,
            0.1875,
            0.203125,
            0.21875,
            0.234375,
            0.25,
            0.265625,
            0.28125,
            0.296875,
            0.3125,
            0.328125,
            0.34375,
            0.359375,
            0.375,
            0.390625,
            0.40625,
            0.421875,
            0.4375,
            0.453125,
            0.46875,
            0.484375,
            0.5,
            0.515625,
            0.53125,
            0.546875,
            0.5625,
            0.578125,
            0.59375,
            0.609375,
            0.625,
            0.640625,
            0.65625,
            0.671875,
            0.6875,
            0.703125,
            0.71875,
            0.734375,
            0.75,
            0.765625,
            0.78125,
            0.796875,
            0.8125,
            0.828125,
            0.84375,
            0.859375,
            0.875,
            0.890625,
            0.90625,
            0.921875,
            0.9375,
            0.953125,
            0.96875,
            0.984375
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputUnipolarRamp.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputUnipolarRamp[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }

        mTest->TEST_ASSERT("testUnipolarRamp generated correct output", badSampleCount == 0);
        
    }
    
    void testSine() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::Sine<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputSine = {
            0,
            0.0980171403295606,
            0.1950903220161282,
            0.2902846772544623,
            0.3826834323650898,
            0.4713967368259976,
            0.5555702330196022,
            0.6343932841636455,
            0.7071067811865475,
            0.7730104533627369,
            0.8314696123025451,
            0.8819212643483549,
            0.9238795325112867,
            0.9569403357322089,
            0.9807852804032304,
            0.9951847266721968,
            1,
            0.9951847266721969,
            0.9807852804032304,
            0.9569403357322089,
            0.9238795325112867,
            0.881921264348355,
            0.8314696123025455,
            0.7730104533627371,
            0.7071067811865476,
            0.6343932841636455,
            0.5555702330196022,
            0.4713967368259978,
            0.3826834323650898,
            0.2902846772544623,
            0.1950903220161286,
            0.09801714032956084,
            1.224646799147353e-16,
            -0.09801714032956059,
            -0.1950903220161284,
            -0.2902846772544622,
            -0.3826834323650897,
            -0.4713967368259976,
            -0.555570233019602,
            -0.6343932841636453,
            -0.7071067811865475,
            -0.7730104533627367,
            -0.8314696123025452,
            -0.8819212643483549,
            -0.9238795325112865,
            -0.9569403357322088,
            -0.9807852804032303,
            -0.9951847266721969,
            -1,
            -0.9951847266721969,
            -0.9807852804032304,
            -0.9569403357322089,
            -0.9238795325112866,
            -0.881921264348355,
            -0.8314696123025456,
            -0.7730104533627369,
            -0.7071067811865477,
            -0.6343932841636459,
            -0.5555702330196022,
            -0.4713967368259979,
            -0.3826834323650904,
            -0.2902846772544624,
            -0.1950903220161287,
            -0.09801714032956052
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputSine.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputSine[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testSine generated correct output", badSampleCount == 0);
        
    }
    
    void testTriangle() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::Triangle<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputTriangle = {
            0,
            0.0625,
            0.125,
            0.1875,
            0.25,
            0.3125,
            0.375,
            0.4375,
            0.5,
            0.5625,
            0.625,
            0.6875,
            0.75,
            0.8125,
            0.875,
            0.9375,
            1,
            0.9375,
            0.875,
            0.8125,
            0.75,
            0.6875,
            0.625,
            0.5625,
            0.5,
            0.4375,
            0.375,
            0.3125,
            0.25,
            0.1875,
            0.125,
            0.0625,
            0,
            -0.0625,
            -0.125,
            -0.1875,
            -0.25,
            -0.3125,
            -0.375,
            -0.4375,
            -0.5,
            -0.5625,
            -0.625,
            -0.6875,
            -0.75,
            -0.8125,
            -0.875,
            -0.9375,
            -1,
            -0.9375,
            -0.875,
            -0.8125,
            -0.75,
            -0.6875,
            -0.625,
            -0.5625,
            -0.5,
            -0.4375,
            -0.375,
            -0.3125,
            -0.25,
            -0.1875,
            -0.125,
            -0.0625
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputTriangle.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputTriangle[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testTriangle generated correct output", badSampleCount == 0);
        
    }
    
    void testConsistentAcrossMultipleChannels() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(10, 128);
        
        test_sample_bundle.generate();
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for(int i = 0; i < test_sample_bundle[0].size(); i++) {
            tempExpected = test_sample_bundle[0][i];
            for(int j = 1; j < test_sample_bundle.channelCount(); j++) {
                temp = test_sample_bundle[j][i];
                if (! mTest->compare(temp, tempExpected, true) ) {
                    badSampleCount++;
                    std::cout << "bad sample " << i << " in channel " << j << " = " << test_sample_bundle[j][i] << std::endl;
                }
            }
        }
        
        mTest->TEST_ASSERT("generated consistent output across multiple channels", badSampleCount == 0);
        
    }

	
};

int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<GeneratorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
