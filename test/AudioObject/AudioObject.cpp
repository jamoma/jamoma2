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
		
        // testing the sampleRate limits with a common generator class
        Jamoma::Sync s;
        
        s.sampleRate = 1000;
        mTest->TEST_ASSERT("setting sampleRate param within range", s.sampleRate == 1000 );
        
        s.sampleRate = 500000;
        mTest->TEST_ASSERT("setting sampleRate param way above range", s.sampleRate == 96000 );
        
        s.sampleRate = -2000;
        mTest->TEST_ASSERT("setting sampleRate param below range", s.sampleRate == 1 );
        
        s.sampleRate = 96010;
        mTest->TEST_ASSERT("setting sampleRate param slightly above range", s.sampleRate == 96000 );
        
        s.sampleRate = 44100;
        mTest->TEST_ASSERT("setting sampleRate param within range", s.sampleRate == 44100 );
        
        
        // testing the sampleRate limits again with a common processing class
        Jamoma::Dcblock dc;
        
        dc.sampleRate = 1000;
        mTest->TEST_ASSERT("setting sampleRate param within range", dc.sampleRate == 1000 );
        
        dc.sampleRate = 500000;
        mTest->TEST_ASSERT("setting sampleRate param way above range", dc.sampleRate == 96000 );
        
        dc.sampleRate = -2000;
        mTest->TEST_ASSERT("setting sampleRate param below range", dc.sampleRate == 1 );
        
        dc.sampleRate = 96010;
        mTest->TEST_ASSERT("setting sampleRate param slightly above range", dc.sampleRate == 96000 );
        
        dc.sampleRate = 44100;
        mTest->TEST_ASSERT("setting sampleRate param within range", dc.sampleRate == 44100 );
        

	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<AudioObjectTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
