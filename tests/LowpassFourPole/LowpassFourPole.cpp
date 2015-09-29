/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Dcblocker class
 
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
		
		
#ifdef NEEDS_ATTENTION // see 
		
		// The following impulse was based on the code found here
		// http://musicdsp.org/archive.php?classid=3#26
		// implemented in Processing by NW, adopting tweaks made in jamoma2.
		// It should correspond to the following settings:
		// cutoff = 1000
		// q = 10.0
		
		Jamoma::SampleVector expectedIR = {
			1.1114094966912524E-4,
			5.185809867004247E-4,
			0.0013566830733495131,
			0.00266711884609515,
			0.004419756543933562,
			0.006540995119517765,
			0.008934880451193566,
			0.011497619575988889,
			0.014127212462044219,
			0.016729524194462317,
			0.01922180477418673,
			0.021534415062963778,
			0.02361132349572916,
			0.025409788493738057,
			0.026899527152547734,
			0.028061584347418934,
			0.028887051817754188,
			0.02937573913186519,
			0.029534863739063902,
			0.029377802449531133,
			0.02892292917914669,
			0.02819255174120884,
			0.0272119523870212,
			0.026008531572689723,
			0.0246110512183134,
			0.023048971903299378,
			0.021351877550629245,
			0.019548980864406137,
			0.01766870286642576,
			0.015738320168397234,
			0.013783674009326336,
			0.01182893551333184,
			0.009896422039881662,
			0.008006459883080358,
			0.006177288918901074,
			0.004425005097042377,
			0.002763536930312534,
			0.0012046523547523686,
			-2.4200747504493246E-4,
			-0.0015688707217329722,
			-0.002770356844647906,
			-0.003842780991240676,
			-0.004784243629542635,
			-0.005594508112436378,
			-0.006274868724514015,
			-0.006828011618719647,
			-0.00725787090172078,
			-0.007569481973642979,
			-0.0077688340695979425,
			-0.007862723787941745,
			-0.007858611224353948,
			-0.007764480162803003,
			-0.007588703605585956,
			-0.007339915756309998,
			-0.007026891403352279,
			-0.006658433488399313,
			-0.0062432694864702305,
			-0.00578995707161646,
			-0.005306799397393739,
			-0.004801770184216497,
			-0.0042824486776811615,
			-0.0037559644235848214,
			-0.0032289516972181694,
			-0.0027075133269751014
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
#endif // #ifdef NEEDS_ATTENTION
		
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
