/** @file
	@ingroup jamoma2
 
	@brief Unit test for the Dcblocker class
 
	@author Timothy Place, Nathan Wolek
 
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#include "Jamoma.h"


class LowpassOnePoleTest {
	
	Jamoma::UnitTest<LowpassOnePoleTest>*	mTest;
	
public:
	LowpassOnePoleTest(Jamoma::UnitTest<LowpassOnePoleTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
	}

	
	void testImpulseResponse()
	{
		Jamoma::LowpassOnePole my_lowpass;
		
		my_lowpass.coefficient = 0.5;
		
		Jamoma::UnitImpulse impulse;
		
		impulse.channelCount = 1;
		impulse.frameCount = 64;
		
		auto out_samples = my_lowpass( impulse() );
		
		// The following impulse was based on the code from jamoma
		// implemented in Processing by NW
		Jamoma::SampleVector expectedIR = {
			0.5,
			0.25,
			0.125,
			0.0625,
			0.03125,
			0.015625,
			0.0078125,
			0.00390625,
			0.001953125,
			9.765625E-4,
			4.8828125E-4,
			2.44140625E-4,
			1.220703125E-4,
			6.103515625E-5,
			3.0517578125E-5,
			1.52587890625E-5,
			7.62939453125E-6,
			3.814697265625E-6,
			1.9073486328125E-6,
			9.5367431640625E-7,
			4.76837158203125E-7,
			2.384185791015625E-7,
			1.1920928955078125E-7,
			5.9604644775390625E-8,
			2.9802322387695312E-8,
			1.4901161193847656E-8,
			7.450580596923828E-9,
			3.725290298461914E-9,
			1.862645149230957E-9,
			9.313225746154785E-10,
			4.6566128730773926E-10,
			2.3283064365386963E-10,
			1.1641532182693481E-10,
			5.820766091346741E-11,
			2.9103830456733704E-11,
			1.4551915228366852E-11,
			7.275957614183426E-12,
			3.637978807091713E-12,
			1.8189894035458565E-12,
			9.094947017729282E-13,
			4.547473508864641E-13,
			2.2737367544323206E-13,
			1.1368683772161603E-13,
			5.6843418860808015E-14,
			2.8421709430404007E-14,
			1.4210854715202004E-14,
			7.105427357601002E-15,
			3.552713678800501E-15,
			1.7763568394002505E-15,
			8.881784197001252E-16,
			4.440892098500626E-16,
			2.220446049250313E-16,
			1.1102230246251565E-16,
			5.551115123125783E-17,
			2.7755575615628914E-17,
			1.3877787807814457E-17,
			6.938893903907228E-18,
			3.469446951953614E-18,
			1.734723475976807E-18,
			8.673617379884035E-19,
			4.3368086899420177E-19,
			2.1684043449710089E-19,
			1.0842021724855044E-19,
			5.421010862427522E-20
		};
		
		int badSampleCount = 0;
		Jamoma::Sample temp = 0.0;
		Jamoma::Sample tempExpected = 0.0;
		
		for (int i = 0; i < expectedIR.size(); i++)
		{
			temp = out_samples[0][0][i];
			tempExpected = expectedIR[i];
			if (! mTest->compare(temp, tempExpected) ) {
				badSampleCount++;
				std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
			}
		}
		
		std::cout << "the impulse response of my_lowpass (1 pole) has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
		
		// testing range limitations
		my_lowpass.coefficient = 0.7;
		mTest->TEST_ASSERT("coefficient setting", my_lowpass.coefficient == 0.7);
		
		my_lowpass.coefficient = -1.0;
		mTest->TEST_ASSERT("low coefficient limiting", my_lowpass.coefficient == 0.0);
		
		my_lowpass.coefficient = 1.2;
		mTest->TEST_ASSERT("high coefficient limiting", my_lowpass.coefficient == 1.0);
	}

};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<LowpassOnePoleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
