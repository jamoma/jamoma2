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
