/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the LowpassFourPole class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class LowpassFourpoleTest {
	
	Jamoma::UnitTest<LowpassFourpoleTest>*	mTest;
	
public:
	LowpassFourpoleTest(Jamoma::UnitTest<LowpassFourpoleTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
	}

	
	void testImpulseResponse()
	{
		Jamoma::LowpassFourPole my_lowpass;
			
		my_lowpass.sampleRate = 44100;
		my_lowpass.frequency = 1000.;
		my_lowpass.resonance = 10.0;
		
		Jamoma::UnitImpulse impulse;
		
		impulse.channelCount = 1;
		impulse.frameCount = 64;
		
		auto out_samples = my_lowpass( impulse() );
		
		

		
		// The following impulse was based on the code found here
		// http://musicdsp.org/archive.php?classid=3#26
		// implemented in Processing by NW, adopting tweaks made in jamoma2.
		// It should correspond to the following settings:
		// cutoff = 1000
		// q = 10.0
		
		Jamoma::SampleVector expectedIR = {
            0.0001111409354565384,
            0.0005185809173325713,
            0.001356682889160042,
            0.002667118485531729,
            0.004419755956128823,
            0.006540994270685398,
            0.008934879326675504,
            0.01149761817960361,
            0.01412721081388471,
            0.01672952232792294,
            0.01922180273273093,
            0.02153441289695431,
            0.02361132125950997,
            0.02540978624306706,
            0.02689952494242021,
            0.02806158223028391,
            0.02888704984210379,
            0.02937573734116469,
            0.02953486217098515,
            0.02937780113545063,
            0.02892292814387115,
            0.02819255100289367,
            0.02721195195725074,
            0.02600853145669125,
            0.02461105141528048,
            0.02304897240680268,
            0.0213518783490958,
            0.01954898194165014,
            0.01766870420221603,
            0.01573832173904799,
            0.01378367578829957,
            0.01182893747184068,
            0.009896424147485519,
            0.008006462108263472,
            0.00617729122962732,
            0.004425007461280003,
            0.002763539316523515,
            0.001204654732341931,
            -0.0002420051353221634,
            -0.001568868447412927,
            -0.002770354661245002,
            -0.00384277892198484,
            -0.00478424169516578,
            -0.005594506331008,
            -0.006274867111324928, 
            -0.006828010186212292, 
            -0.007257869659464013, 
            -0.007569480928348766, 
            -0.007768833225177001, 
            -0.007862723145594849, 
            -0.007858610782695312, 
            -0.007764479918011999, 
            -0.007588703551583271, 
            -0.007339915884954236, 
            -0.007026891704653052, 
            -0.006658433950742859, 
            -0.006243270096853714, 
            -0.005789957815887236, 
            -0.005306800260490047, 
            -0.004801771150406263, 
            -0.004282449730795825, 
            -0.003755965547245381, 
            -0.003228952875050936, 
            -0.002707514542814925
		};
		
		int badSampleCount = 0;
		Jamoma::Sample temp = 0.0;
		Jamoma::Sample tempExpected = 0.0;
		
		for (int i = 0; i < expectedIR.size(); i++) {
			temp = out_samples[0][0][i];
			tempExpected = expectedIR[i];
			if (! mTest->compare(temp, tempExpected) ) {
				badSampleCount++;
				std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
			}
		}
		
		std::cout << "the impulse response of my_lowpass (4 pole) has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);

		
		// Test range limiting
		my_lowpass.frequency = 100.0;
		mTest->TEST_ASSERT("frequency setting is correct", my_lowpass.frequency == 100.0);
		
		my_lowpass.frequency = 5.0;
		mTest->TEST_ASSERT("low frequency is clipped", my_lowpass.frequency == 20.0);
		
		// TODO: boundaries for this object need to change when the sampleRate changes -- currently they don't!
		// So we do this test with the initial sampleRate instead of with `my_lowpass.sampleRate`
		my_lowpass.frequency = 100000;
		mTest->TEST_ASSERT("high frequency is clipped", my_lowpass.frequency < 96000 * 0.5);
		
		// resonance is not clipped at the moment, so we can do irrational bad things...  we should change this
		my_lowpass.resonance = 100.0;
		mTest->TEST_ASSERT("insane resonance is not clipped", my_lowpass.resonance == 100.0);
		
		my_lowpass.resonance = -5.0;
		mTest->TEST_ASSERT("negative resonance is not clipped", my_lowpass.resonance == -5.0);
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<LowpassFourpoleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
