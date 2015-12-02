/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Allpass class
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class AllpassTest {
	
	Jamoma::UnitTest<AllpassTest>*	mTest;
	
public:
	AllpassTest(Jamoma::UnitTest<AllpassTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
	}

	
	void testImpulseResponse()
	{
		Jamoma::UnitImpulse impulse;
		impulse.channelCount = 1;
		impulse.frameCount = 64;

		Jamoma::Allpass1 allpass;
		allpass.sampleRate = 44100;
		allpass.delay = 1;
		allpass.gain = 0.5;
		
		auto out_samples = allpass( impulse() );
		
		// coefficients calculated in Octave
		//	a = [0.5, 1.0];	% numerator (fir)
		//	b = [1.0, 0.5];	% denominator (iir)
		//	i = impz(a, b, 64);
		Jamoma::SampleVector expectedIR = {
			0.500000000000000    ,
			0.750000000000000    ,
			-0.375000000000000   ,
			0.187500000000000    ,
			-0.0937500000000000  ,
			0.0468750000000000   ,
			-0.0234375000000000  ,
			0.0117187500000000   ,
			-0.00585937500000000 ,
			0.00292968750000000  ,
			-0.00146484375000000 ,
			0.000732421875000000 ,
			-0.000366210937500000,
			0.000183105468750000 ,
			-9.15527343750000e-05,
			4.57763671875000e-05 ,
			-2.28881835937500e-05,
			1.14440917968750e-05 ,
			-5.72204589843750e-06,
			2.86102294921875e-06 ,
			-1.43051147460938e-06,
			7.15255737304688e-07 ,
			-3.57627868652344e-07,
			1.78813934326172e-07 ,
			-8.94069671630859e-08,
			4.47034835815430e-08 ,
			-2.23517417907715e-08,
			1.11758708953857e-08 ,
			-5.58793544769287e-09,
			2.79396772384644e-09 ,
			-1.39698386192322e-09,
			6.98491930961609e-10 ,
			-3.49245965480804e-10,
			1.74622982740402e-10 ,
			-8.73114913702011e-11,
			4.36557456851006e-11 ,
			-2.18278728425503e-11,
			1.09139364212751e-11 ,
			-5.45696821063757e-12,
			2.72848410531878e-12 ,
			-1.36424205265939e-12,
			6.82121026329696e-13 ,
			-3.41060513164848e-13,
			1.70530256582424e-13 ,
			-8.52651282912120e-14,
			4.26325641456060e-14 ,
			-2.13162820728030e-14,
			1.06581410364015e-14 ,
			-5.32907051820075e-15,
			2.66453525910038e-15 ,
			-1.33226762955019e-15,
			6.66133814775094e-16 ,
			-3.33066907387547e-16,
			1.66533453693773e-16 ,
			-8.32667268468867e-17,
			4.16333634234434e-17 ,
			-2.08166817117217e-17,
			1.04083408558608e-17 ,
			-5.20417042793042e-18,
			2.60208521396521e-18 ,
			-1.30104260698261e-18,
			6.50521303491303e-19 ,
			-3.25260651745651e-19,
			1.62630325872826e-19
			
		};
		
		Jamoma::Sample	temp = 0.0;
		Jamoma::Sample	tempExpected = 0.0;
		int				badSampleCount = 0;
		
		for (int i=0; i < expectedIR.size(); i++) {
			temp = out_samples[0][0][i];
			tempExpected = expectedIR[i];
			
			// NOTE: setting comparison ULPs to 28 was done by trial and error -- roundoff accumulates signficantly due to recursive implementation
			if (! mTest->compare(temp, tempExpected, true, 28) ) {
				badSampleCount++;
				std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
			}
		}
		
		std::cout << "the impulse response of my_comb has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<AllpassTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
