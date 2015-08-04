/** @file
	@ingroup jamoma2
 
	@brief Unit test for the Dcblocker class
 
	@author Timothy Place, Nathan Wolek
 
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#include "Jamoma.h"


class DcblockTest {
	
	Jamoma::UnitTest<DcblockTest>*	mTest;
	
public:
	DcblockTest(Jamoma::UnitTest<DcblockTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
	}

	
	void testImpulseResponse()
	{
		Jamoma::Dcblock			my_dcblock;
		Jamoma::UnitImpulse		impulse;
		
		impulse.channelCount = 1;
		impulse.frameCount = 64;
		
		auto out_samples = my_dcblock( impulse() );
		
		// The following impulse was based on the code from jamoma
		// implemented in Processing by NW
		
		// TODO: add the actual Processing code that was used as a comment here.
		
		Jamoma::SampleVector expectedIR = {
			1.0,
			-2.99990177154541E-4,
			-2.999001830481518E-4,
			-2.998102159391105E-4,
			-2.997202758193182E-4,
			-2.9963036268067835E-4,
			-2.995404765150969E-4,
			-2.994506173144822E-4,
			-2.99360785070745E-4,
			-2.992709797757985E-4,
			-2.9918120142155834E-4,
			-2.9909144999994256E-4,
			-2.9900172550287167E-4,
			-2.9891202792226853E-4,
			-2.988223572500585E-4,
			-2.987327134781693E-4,
			-2.986430965985311E-4,
			-2.9855350660307656E-4,
			-2.984639434837406E-4,
			-2.9837440723246066E-4,
			-2.9828489784117663E-4,
			-2.9819541530183075E-4,
			-2.981059596063677E-4,
			-2.9801653074673455E-4,
			-2.9792712871488084E-4,
			-2.978377535027585E-4,
			-2.9774840510232194E-4,
			-2.9765908350552783E-4,
			-2.9756978870433537E-4,
			-2.9748052069070613E-4,
			-2.973912794566041E-4,
			-2.973020649939957E-4,
			-2.972128772948497E-4,
			-2.971237163511374E-4,
			-2.970345821548324E-4,
			-2.9694547469791076E-4,
			-2.968563939723509E-4,
			-2.9676733997013367E-4,
			-2.9667831268324234E-4,
			-2.9658931210366256E-4,
			-2.9650033822338246E-4,
			-2.964113910343924E-4,
			-2.963224705286854E-4,
			-2.9623357669825666E-4,
			-2.961447095351038E-4,
			-2.96055869031227E-4,
			-2.959670551786287E-4,
			-2.9587826796931375E-4,
			-2.9578950739528944E-4,
			-2.957007734485655E-4,
			-2.956120661211539E-4,
			-2.955233854050692E-4,
			-2.954347312923282E-4,
			-2.953461037749502E-4,
			-2.9525750284495686E-4,
			-2.951689284943722E-4,
			-2.9508038071522267E-4,
			-2.9499185949953706E-4,
			-2.949033648393467E-4,
			-2.9481489672668505E-4,
			-2.947264551535882E-4,
			-2.9463804011209453E-4,
			-2.9454965159424483E-4,
			-2.944612895920823E-4
		};
		
		int				badSampleCount = 0;
		Jamoma::Sample	temp = 0.0;
		Jamoma::Sample	tempExpected = 0.0;
		
		for (int i=0; i < expectedIR.size(); i++) {
			temp = out_samples[0][0][i];
			tempExpected = expectedIR[i];
			if ( ! mTest->compare(temp, tempExpected ) ) {
				badSampleCount++;
				mTest->log("sample %i had a difference of %f", i, std::fabs(temp - tempExpected));
			}
		}
		
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
		if (badSampleCount)
			mTest->log("the impulse response of my_dcblock has %i bad sample(s)", badSampleCount);
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<DcblockTest>	aUnitTestInstance;
	return 0;
}
