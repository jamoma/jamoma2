/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the UnitImpulse class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class UnitImpulseTest {
	
	Jamoma::UnitTest<UnitImpulseTest>*	mTest;
	
public:
	UnitImpulseTest(Jamoma::UnitTest<UnitImpulseTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
		testImpulseResponseStereo();
	}

	
	void testImpulseResponse()
	{
		Jamoma::UnitImpulse my_impulse;
		
		my_impulse.channelCount = 1;
		my_impulse.frameCount = 64;
		
		auto output = my_impulse();
		
		Jamoma::SampleVector expectedImpulse = {
			1.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0,
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
		
		int badSampleCount = 0;
		
		for (int i = 0; i < expectedImpulse.size(); i++) {
			if (expectedImpulse[i] != output[0][0][i]) {
				badSampleCount++;
				std::cout << "sample " << i << " expected " << expectedImpulse[i] << " but instead was " << output[0][0][i] << std::endl;
			}
		}
		
		std::cout << "unit impulse has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
	}
	
	
	
	void testImpulseResponseStereo()
	{
		Jamoma::UnitImpulse my_impulse;
		
		my_impulse.channelCount = 2;
		my_impulse.frameCount = 8;
		
		auto output = my_impulse();
		
		Jamoma::SampleVector expectedImpulse = { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
		
		int badSampleCount = 0;
		
		for (int i = 0; i < expectedImpulse.size(); i++) {
			if (expectedImpulse[i] != output[0][0][i]) {
				badSampleCount++;
				std::cout << "left sample " << i << " expected " << expectedImpulse[i] << " but instead was " << output[0][0][i] << std::endl;
			}
			if (expectedImpulse[i] != output[0][1][i]) {
				badSampleCount++;
				std::cout << "right sample " << i << " expected " << expectedImpulse[i] << " but instead was " << output[0][1][i] << std::endl;
			}
		}
		
		std::cout << "unit impulse has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<UnitImpulseTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
