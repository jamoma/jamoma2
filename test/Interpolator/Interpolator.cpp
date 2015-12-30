/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for Interpolator classes
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class InterpolatorTest {
	
	Jamoma::UnitTest<InterpolatorTest>*	mTest;
	
public:
	InterpolatorTest(Jamoma::UnitTest<InterpolatorTest>* test)
	: mTest(test)
	{
        testNone();
        testLinear();
		testCosine();
		testCubic();
        testHermite();
        testSpline();
    }
    
    void testNone() {
        Jamoma::Interpolator::None<Jamoma::Sample> my_interp;
        
        auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        auto    x3 =  4.0;
        
        auto out = my_interp(x0);
        
        mTest->TEST_ASSERT("testNone with 1 sample produced correct output", out == x0);
        
        auto out2 = my_interp(x0,x1,0.25);
        
        mTest->TEST_ASSERT("testNone with 2 samples produced correct output", out2 == x0);
        
        auto out3 = my_interp(x0,x1,x2,x3,0.25);
        
        mTest->TEST_ASSERT("testNone with 4 samples produced correct output", out3 == x0);
        
    }

	
	void testLinear() {
		int		badSampleCount = 0;
        Jamoma::Interpolator::Linear<Jamoma::Sample> my_interp;
        
		auto 	x0 = -1.0;
		auto	x1 =  2.0;
	
        // The following output was generated using the Octave code
        // in InterpolatorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputLinear = {
            -0.953125,
            -0.90625,
            -0.859375,
            -0.8125,
            -0.765625,
            -0.71875,
            -0.671875,
            -0.625,
            -0.578125,
            -0.53125,
            -0.484375,
            -0.4375,
            -0.390625,
            -0.34375,
            -0.296875,
            -0.25,
            -0.203125,
            -0.15625,
            -0.109375,
            -0.0625,
            -0.015625,
            0.03125,
            0.078125,
            0.125,
            0.171875,
            0.21875,
            0.265625,
            0.3125,
            0.359375,
            0.40625,
            0.453125, 
            0.5, 
            0.546875, 
            0.59375, 
            0.640625, 
            0.6875, 
            0.734375, 
            0.78125, 
            0.828125, 
            0.875, 
            0.921875, 
            0.96875, 
            1.015625, 
            1.0625, 
            1.109375, 
            1.15625, 
            1.203125, 
            1.25, 
            1.296875, 
            1.34375, 
            1.390625, 
            1.4375, 
            1.484375, 
            1.53125, 
            1.578125, 
            1.625, 
            1.671875, 
            1.71875, 
            1.765625, 
            1.8125, 
            1.859375, 
            1.90625, 
            1.953125, 
            2
        };
	
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double delta = 0.0;
        
        for (int i = 0; i < expectedOutputLinear.size(); i++) {
            delta = (i + 1.0) / 64.0;
            temp = my_interp(x0,x1,delta);
            tempExpected = expectedOutputLinear[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }

		mTest->TEST_ASSERT("testLinear produced correct interpolation output", badSampleCount == 0);
	}
	
	
	void testCosine() {
        int		badSampleCount = 0;
        Jamoma::Interpolator::Cosine<Jamoma::Sample> my_interp;
        
        //auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        //auto    x3 =  4.0;
        
        // The following output was generated using the Octave code
        // in InterpolatorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputCosine = {
            1.999397728102586,
            1.997592363336099,
            1.994588254982391,
            1.990392640201615,
            1.985015626597272,
            1.978470167866104,
            1.97077203259151,
            1.961939766255643,
            1.951994646561722,
            1.940960632174177,
            1.928864305000136,
            1.915734806151273,
            1.901603765740322,
            1.886505226681368,
            1.87047556267748,
            1.853553390593274,
            1.835779477423509,
            1.817196642081823,
            1.797849652246217,
            1.777785116509801,
            1.757051372096611,
            1.735698368412999,
            1.713777546715141,
            1.691341716182545,
            1.66844492669611,
            1.645142338627231,
            1.621490089951632,
            1.597545161008064,
            1.573365237227681,
            1.54900857016478,
            1.524533837163709,
            1.5,
            1.475466162836291,
            1.45099142983522,
            1.426634762772319,
            1.402454838991936,
            1.378509910048368,
            1.354857661372769,
            1.33155507330389,
            1.308658283817455,
            1.286222453284859,
            1.264301631587001,
            1.242948627903389,
            1.222214883490199,
            1.202150347753783,
            1.182803357918177,
            1.164220522576491,
            1.146446609406726,
            1.129524437322521,
            1.113494773318632,
            1.098396234259678,
            1.084265193848727,
            1.071135694999864,
            1.059039367825823,
            1.048005353438278,
            1.038060233744357,
            1.02922796740849,
            1.021529832133896,
            1.014984373402728,
            1.009607359798385,
            1.005411745017609,
            1.002407636663902,
            1.000602271897414,
            1
        };
		
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double delta = 0.0;
        
        for (int i = 0; i < expectedOutputCosine.size(); i++) {
            delta = (i + 1.0) / 64.0;
            temp = my_interp(x1,x2,delta);
            tempExpected = expectedOutputCosine[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
		
		mTest->TEST_ASSERT("testCosine produced correct interpolation output", badSampleCount == 0);
	}
	

	void testCubic() {
        int		badSampleCount = 0;
        Jamoma::Interpolator::Cubic<Jamoma::Sample> my_interp;
        
        auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        auto    x3 =  4.0;
        
        // The following output was generated using the Octave code
        // in InterpolatorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputCubic = {
            2.029075622558594,
            2.05389404296875,
            2.074592590332031,
            2.09130859375,
            2.104179382324219,
            2.11334228515625,
            2.118934631347656,
            2.12109375,
            2.119956970214844,
            2.11566162109375,
            2.108345031738281,
            2.09814453125,
            2.085197448730469,
            2.06964111328125,
            2.051612854003906,
            2.03125,
            2.008689880371094,
            1.98406982421875,
            1.957527160644531,
            1.92919921875,
            1.899223327636719,
            1.86773681640625,
            1.834877014160156,
            1.80078125,
            1.765586853027344,
            1.72943115234375,
            1.692451477050781,
            1.65478515625,
            1.616569519042969,
            1.57794189453125,
            1.539039611816406,
            1.5,
            1.460960388183594,
            1.42205810546875,
            1.383430480957031,
            1.34521484375,
            1.307548522949219,
            1.27056884765625,
            1.234413146972656,
            1.19921875,
            1.165122985839844,
            1.13226318359375,
            1.100776672363281,
            1.07080078125,
            1.042472839355469,
            1.01593017578125,
            0.9913101196289062,
            0.96875,
            0.9483871459960938,
            0.93035888671875,
            0.9148025512695312,
            0.90185546875,
            0.8916549682617188,
            0.88433837890625,
            0.8800430297851562,
            0.87890625,
            0.8810653686523438,
            0.88665771484375,
            0.8958206176757812,
            0.90869140625,
            0.9254074096679688,
            0.94610595703125,
            0.9709243774414062,
            1
        };
		
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double delta = 0.0;
        
        for (int i = 0; i < expectedOutputCubic.size(); i++) {
            delta = (i + 1.0) / 64.0;
            temp = my_interp(x0,x1,x2,x3,delta);
            tempExpected = expectedOutputCubic[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
		
		mTest->TEST_ASSERT("testCubic produced correct interpolation output", badSampleCount == 0);
	}
    
    void testHermite() {
        int		badSampleCount = 0;
        Jamoma::Interpolator::Hermite<Jamoma::Sample> my_interp;
        my_interp.bias = 0.5;
        my_interp.tension = 0.5;
        
        auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        auto    x3 =  4.0;
        
        // The following output was generated using the Octave code
        // in InterpolatorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputHermite = {
            2.014415740966797,
            2.026458740234375,
            2.036197662353516,
            2.043701171875,
            2.049037933349609,
            2.052276611328125,
            2.053485870361328,
            2.052734375,
            2.050090789794922,
            2.045623779296875,
            2.039402008056641,
            2.031494140625,
            2.021968841552734,
            2.010894775390625,
            1.998340606689453,
            1.984375,
            1.969066619873047,
            1.952484130859375,
            1.934696197509766,
            1.915771484375,
            1.895778656005859,
            1.874786376953125,
            1.852863311767578,
            1.830078125,
            1.806499481201172,
            1.782196044921875,
            1.757236480712891,
            1.731689453125,
            1.705623626708984,
            1.679107666015625,
            1.652210235595703,
            1.625,
            1.597545623779297,
            1.569915771484375,
            1.542179107666016,
            1.514404296875,
            1.486660003662109,
            1.459014892578125,
            1.431537628173828,
            1.404296875,
            1.377361297607422,
            1.350799560546875,
            1.324680328369141,
            1.299072265625,
            1.274044036865234,
            1.249664306640625,
            1.226001739501953,
            1.203125,
            1.181102752685547,
            1.160003662109375,
            1.139896392822266,
            1.120849609375,
            1.102931976318359,
            1.086212158203125,
            1.070758819580078,
            1.056640625,
            1.043926239013672,
            1.032684326171875,
            1.022983551025391,
            1.014892578125,
            1.008480072021484,
            1.003814697265625,
            1.000965118408203,
            1
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double delta = 0.0;
        
        for (int i = 0; i < expectedOutputHermite.size(); i++) {
            delta = (i + 1.0) / 64.0;
            temp = my_interp(x0,x1,x2,x3,delta);
            tempExpected = expectedOutputHermite[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testHermite produced correct interpolation output", badSampleCount == 0);
    }
    
    void testSpline() {
        int		badSampleCount = 0;
        Jamoma::Interpolator::Spline<Jamoma::Sample> my_interp;
        
        auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        auto    x3 =  4.0;
        
        // The following output was generated using the Octave code
        // in InterpolatorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputSpline = {
            2.014175415039062,
            2.0255126953125,
            2.034103393554688,
            2.0400390625,
            2.043411254882812,
            2.0443115234375,
            2.042831420898438,
            2.0390625,
            2.033096313476562,
            2.0250244140625,
            2.014938354492188,
            2.0029296875,
            1.989089965820312,
            1.9735107421875,
            1.956283569335938,
            1.9375,
            1.917251586914062,
            1.8956298828125,
            1.872726440429688,
            1.8486328125,
            1.823440551757812,
            1.7972412109375,
            1.770126342773438,
            1.7421875,
            1.713516235351562,
            1.6842041015625,
            1.654342651367188,
            1.6240234375,
            1.593338012695312,
            1.5623779296875,
            1.531234741210938,
            1.5,
            1.468765258789062,
            1.4376220703125,
            1.406661987304688,
            1.3759765625,
            1.345657348632812,
            1.3157958984375,
            1.286483764648438,
            1.2578125,
            1.229873657226562,
            1.2027587890625,
            1.176559448242188,
            1.1513671875,
            1.127273559570312,
            1.1043701171875,
            1.082748413085938,
            1.0625,
            1.043716430664062,
            1.0264892578125,
            1.010910034179688,
            0.9970703125,
            0.9850616455078125,
            0.9749755859375,
            0.9669036865234375,
            0.9609375,
            0.9571685791015625,
            0.9556884765625,
            0.9565887451171875,
            0.9599609375,
            0.9658966064453125,
            0.9744873046875,
            0.9858245849609375,
            1
        };
        
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double delta = 0.0;
        
        for (int i = 0; i < expectedOutputSpline.size(); i++) {
            delta = (i + 1.0) / 64.0;
            temp = my_interp(x0,x1,x2,x3,delta);
            tempExpected = expectedOutputSpline[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }
        
        mTest->TEST_ASSERT("testSpline produced correct interpolation output", badSampleCount == 0);
    }

};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<InterpolatorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
