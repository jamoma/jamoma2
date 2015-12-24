/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Dcblocker class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

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
		
		Jamoma::SampleVector expectedIR = generateReferenceImpulseResponse();
		
		int				badSampleCount = 0;
		Jamoma::Sample	temp = 0.0;
		Jamoma::Sample	tempExpected = 0.0;
		
		for (int i=0; i < expectedIR.size(); i++) {
			temp = out_samples[0][0][i];
			tempExpected = expectedIR[i];
			if ( ! mTest->compare(temp, tempExpected ) ) {
				badSampleCount++;
				mTest->log("sample %i had a difference of %.10f", i, std::fabs(temp - tempExpected));
			}
		}
		
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
		if (badSampleCount)
			mTest->log("the impulse response of my_dcblock has %i bad sample(s)", badSampleCount);
	}
	
	
	// Generate an impulse response from a set of coefficients
	// TODO: factor this out into the core as it is generally useful
	std::vector<double> generateReferenceImpulseResponse()
	{
		int		N = 64;								// size of the impulse response
		Jamoma::SampleVector	a = {1.0, -1.0};	// feedforward coefficients (numerator)
		Jamoma::SampleVector	b = {1.0, -0.9997};	// feedback coefficients (denominator)
		Jamoma::SampleVector	x(N);				// input -- feedforward history
		Jamoma::SampleVector	y(N);				// output -- feedback history
		
		std::fill_n(x.begin(), N, 0.0);
		std::fill_n(y.begin(), N, 0.0);
		x[0] = 1.0;
		
		for (int n=0; n<N; n++) {
			int i;
			
			for (i=0; i<a.size(); i++) {
				Jamoma::Sample	sample = x[n-i];
				
				if (n-i < 0 )
					y[n] += 0.0;
				else
					y[n] += ( a[i] * sample );
			}
			
			// ignore b[0] and assume it is normalized to 1.0
			for (i=1; i<b.size(); i++) {
				if (n-i < 0)
					y[n] -= 0.0;
				else
					y[n] -= ( b[i] * y[n - i] );
			}
		}
		return y;
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<DcblockTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
