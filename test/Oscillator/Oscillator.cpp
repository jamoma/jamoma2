/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Oscillator class
 
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class OscillatorTest {
	
	Jamoma::UnitTest<OscillatorTest>*	mTest;
	
public:
	OscillatorTest(Jamoma::UnitTest<OscillatorTest>* test)
	: mTest(test)
	{
		testParameters();
	}

	
	void testParameters()
	{
		/*
		Jamoma::Oscillator my_sine;
		
		my_sine.channelCount = 1;
		my_sine.frameCount = 64;
		*/
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<OscillatorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
