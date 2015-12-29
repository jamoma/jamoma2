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
        testUnipolarRamp();
        testSine();
        testTriangle();
        //testGenerateFunctions();
	}
    
    void testUnipolarRamp() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::UnipolarRamp<Jamoma::Sample>>();
        
        // The following output will be generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        // For now, it is just zeros
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
        
        // The following output will be generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        // For now, it is just zeros
        Jamoma::SampleVector expectedOutputSine = {
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0
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
        
        // The following output will be generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        // For now, it is just zeros
        Jamoma::SampleVector expectedOutputTriangle = {
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0
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
    
    void testGenerateFunctions() {
        
        Jamoma::SampleBundle	test_sample_bundle(4, 128);
        
        test_sample_bundle.generate();
        
        for(int i = 0; i < test_sample_bundle[0].size(); i++) {
            for(int j = 0; j < test_sample_bundle.channelCount(); j++) {
                std::cout << "sample " << i << " in channel " << j << " = " << test_sample_bundle[j][i] << std::endl;
            }
        }
        
        
        test_sample_bundle.generate<Jamoma::Generator::Triangle<Jamoma::Sample>>();
        for (auto i=0; i < test_sample_bundle[0].size(); ++i) {
            for (auto j=0; j < test_sample_bundle.channelCount(); ++j)
                std::cout << "tri sample " << i << " in channel " << j << " = " << test_sample_bundle[j][i] << std::endl;
        }
        
    }

	
};

int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<GeneratorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
