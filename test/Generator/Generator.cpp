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
        testUnipolarSine();
        testCosine();
        testUnipolarCosine();
        testTriangle();
        testUnipolarTriangle();
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
        
        badSampleCount = 0;
        temp = 0.0;
        tempExpected = 0.0;
        
        Jamoma::SampleBundle	test_sample_bundle2(1, 64);
        
        test_sample_bundle2.generate<Jamoma::Generator::Sawtooth<Jamoma::Sample>>();
        
        for (int i = 0; i < expectedOutputRamp.size(); i++) {
            temp = test_sample_bundle2[0][i];
            tempExpected = expectedOutputRamp[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("using UnipolarSawtooth generated same output as Ramp", badSampleCount == 0);
        
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
        
        badSampleCount = 0;
        temp = 0.0;
        tempExpected = 0.0;
        
        Jamoma::SampleBundle	test_sample_bundle2(1, 64);
        
        test_sample_bundle2.generate<Jamoma::Generator::UnipolarSawtooth<Jamoma::Sample>>();
        
        for (int i = 0; i < expectedOutputUnipolarRamp.size(); i++) {
            temp = test_sample_bundle2[0][i];
            tempExpected = expectedOutputUnipolarRamp[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("using UnipolarSawtooth generated same output as UnipolarRamp", badSampleCount == 0);
        
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
    
    void testUnipolarSine() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::UnipolarSine<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputUnipolarSine = {
            0.5,
            0.5490085701647803,
            0.5975451610080641,
            0.6451423386272311,
            0.6913417161825449,
            0.7356983684129988,
            0.7777851165098011,
            0.8171966420818227,
            0.8535533905932737,
            0.8865052266813684,
            0.9157348061512726,
            0.9409606321741775,
            0.9619397662556434,
            0.9784701678661045,
            0.9903926402016152,
            0.9975923633360984,
            1,
            0.9975923633360985,
            0.9903926402016152,
            0.9784701678661045,
            0.9619397662556434,
            0.9409606321741775,
            0.9157348061512727,
            0.8865052266813686,
            0.8535533905932737,
            0.8171966420818227,
            0.7777851165098011,
            0.735698368412999,
            0.6913417161825449,
            0.6451423386272311,
            0.5975451610080643,
            0.5490085701647804,
            0.5000000000000001,
            0.4509914298352197,
            0.4024548389919358,
            0.3548576613727689,
            0.3086582838174552,
            0.2643016315870012,
            0.222214883490199,
            0.1828033579181774,
            0.1464466094067263,
            0.1134947733186317,
            0.08426519384872738,
            0.05903936782582253,
            0.03806023374435674,
            0.02152983213389559,
            0.00960735979838484,
            0.002407636663901536,
            0,
            0.002407636663901536,
            0.009607359798384785,
            0.02152983213389553,
            0.03806023374435669,
            0.05903936782582248,
            0.08426519384872722,
            0.1134947733186316,
            0.1464466094067262,
            0.182803357918177,
            0.2222148834901989,
            0.264301631587001,
            0.3086582838174548,
            0.3548576613727688,
            0.4024548389919356,
            0.4509914298352197
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputUnipolarSine.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputUnipolarSine[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testSine generated correct output", badSampleCount == 0);
        
    }

    
    void testCosine() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::Cosine<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputCosine = {
            1,
            0.9951847266721969,
            0.9807852804032304,
            0.9569403357322088,
            0.9238795325112867,
            0.881921264348355,
            0.8314696123025452,
            0.773010453362737,
            0.7071067811865476,
            0.6343932841636456,
            0.5555702330196023,
            0.4713967368259978,
            0.3826834323650898,
            0.2902846772544623,
            0.1950903220161283,
            0.09801714032956077,
            6.123233995736766e-17,
            -0.09801714032956066,
            -0.1950903220161282,
            -0.2902846772544622,
            -0.3826834323650897,
            -0.4713967368259977,
            -0.555570233019602,
            -0.6343932841636453,
            -0.7071067811865475,
            -0.773010453362737,
            -0.8314696123025453,
            -0.8819212643483549,
            -0.9238795325112867,
            -0.9569403357322088,
            -0.9807852804032304,
            -0.9951847266721968,
            -1,
            -0.9951847266721969,
            -0.9807852804032304,
            -0.9569403357322089,
            -0.9238795325112867,
            -0.881921264348355,
            -0.8314696123025455,
            -0.7730104533627371,
            -0.7071067811865477,
            -0.6343932841636459,
            -0.5555702330196022,
            -0.4713967368259979,
            -0.3826834323650903,
            -0.2902846772544624,
            -0.1950903220161287,
            -0.09801714032956045,
            -1.83697019872103e-16,
            0.09801714032956009,
            0.1950903220161283,
            0.2902846772544621,
            0.38268343236509,
            0.4713967368259976,
            0.5555702330196018,
            0.6343932841636456,
            0.7071067811865475,
            0.7730104533627367,
            0.8314696123025452,
            0.8819212643483549,
            0.9238795325112865,
            0.9569403357322088,
            0.9807852804032303,
            0.9951847266721969
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputCosine.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputCosine[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testSine generated correct output", badSampleCount == 0);
        
    }
    
    void testUnipolarCosine() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::UnipolarCosine<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputUnipolarCosine = {
            1,
            0.9975923633360985,
            0.9903926402016152,
            0.9784701678661044,
            0.9619397662556434,
            0.9409606321741775,
            0.9157348061512727,
            0.8865052266813684,
            0.8535533905932737,
            0.8171966420818229,
            0.7777851165098011,
            0.735698368412999,
            0.6913417161825449,
            0.6451423386272311,
            0.5975451610080642,
            0.5490085701647804,
            0.5,
            0.4509914298352197,
            0.4024548389919359,
            0.3548576613727689,
            0.3086582838174551,
            0.2643016315870012,
            0.222214883490199,
            0.1828033579181774,
            0.1464466094067263,
            0.1134947733186315,
            0.08426519384872733,
            0.05903936782582253,
            0.03806023374435663,
            0.02152983213389559,
            0.009607359798384785,
            0.002407636663901591,
            0,
            0.002407636663901536,
            0.009607359798384785,
            0.02152983213389553,
            0.03806023374435663,
            0.05903936782582248,
            0.08426519384872727,
            0.1134947733186314,
            0.1464466094067262,
            0.182803357918177,
            0.2222148834901989,
            0.264301631587001,
            0.3086582838174549,
            0.3548576613727688,
            0.4024548389919357,
            0.4509914298352198,
            0.4999999999999999,
            0.54900857016478,
            0.5975451610080641,
            0.645142338627231,
            0.691341716182545,
            0.7356983684129987,
            0.7777851165098009,
            0.8171966420818229,
            0.8535533905932737,
            0.8865052266813683,
            0.9157348061512727,
            0.9409606321741775,
            0.9619397662556433,
            0.9784701678661044,
            0.9903926402016152,
            0.9975923633360985
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputUnipolarCosine.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputUnipolarCosine[i];
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
    
    void testUnipolarTriangle() {
        int		badSampleCount = 0;
        Jamoma::SampleBundle	test_sample_bundle(1, 64);
        
        test_sample_bundle.generate<Jamoma::Generator::UnipolarTriangle<Jamoma::Sample>>();
        
        // The following output was generated using the Octave code
        // in GeneratorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputUnipolarTriangle = {
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
            0.96875,
            1,
            0.96875,
            0.9375,
            0.90625,
            0.875,
            0.84375,
            0.8125,
            0.78125,
            0.75,
            0.71875,
            0.6875,
            0.65625,
            0.625,
            0.59375,
            0.5625,
            0.53125,
            0.5,
            0.46875,
            0.4375,
            0.40625,
            0.375,
            0.34375,
            0.3125,
            0.28125,
            0.25,
            0.21875,
            0.1875,
            0.15625,
            0.125,
            0.09375,
            0.0625,
            0.03125,
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
            0.46875
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        
        for (int i = 0; i < expectedOutputUnipolarTriangle.size(); i++) {
            temp = test_sample_bundle[0][i];
            tempExpected = expectedOutputUnipolarTriangle[i];
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
