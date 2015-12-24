/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for general features of AudioObject class
 
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class AudioObjectTest {
	
	Jamoma::UnitTest<AudioObjectTest>*	mTest;
	
public:
	AudioObjectTest(Jamoma::UnitTest<AudioObjectTest>* test)
	: mTest(test)
	{
		testSampleRateLimits();
	}

	
	void testSampleRateLimits()
	{
		// do some testing here
	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<AudioObjectTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
