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
		testParameterSetting();
        testChangingPhase();
	}

	
	void testParameterSetting()
	{
		Jamoma::Oscillator my_sine;
        // default sampleRate is 96000, therefore frequency parameter range is -46000 to 46000
        
        // NW: Values for frequency that are out of bounds get FOLDED
        
        my_sine.frequency = 440;
        mTest->TEST_ASSERT("setting frequency parameter within range", my_sine.frequency == 440 );
        
        my_sine.frequency = -40;
        mTest->TEST_ASSERT("setting frequency parameter within range 2", my_sine.frequency == -40 );
        
        my_sine.frequency = -50000;
        // 2000 below range, so it will fold back to -46000
        mTest->TEST_ASSERT("setting frequency parameter below range", my_sine.frequency == -46000 );
        
        my_sine.frequency = 60000;
        // 12000 above range, so it will fold back to 36000
        mTest->TEST_ASSERT("setting frequency parameter above range", my_sine.frequency == 36000 );
        
        //std::cout << "frequency = " << my_sine.frequency << std::endl;
        
        // NW: Values for frequency that are out of bounds get WRAPPED
        
        mTest->TEST_ASSERT("default phase is 0.0", my_sine.initialphase == 0.0 );
        
        my_sine.initialphase = 0.25;
        mTest->TEST_ASSERT("setting initialphase parameter within range", my_sine.initialphase == 0.25 );
        
        my_sine.initialphase = -0.2;
        // 0.2 below range, so it will wrap back to 0.8
        mTest->TEST_ASSERT("setting initialphase parameter below range",
                           mTest->compare(double(my_sine.initialphase),0.8,true,8 ));
        
        my_sine.initialphase = 1.3;
        // 0.3 above range, so it will wrap back to 0.3
        mTest->TEST_ASSERT("setting initialphase parameter above range",
                           mTest->compare(double(my_sine.initialphase),0.3,true,8 ));
        
        my_sine.initialphase = 0.75;
        mTest->TEST_ASSERT("setting initialphase parameter within range 2", my_sine.initialphase == 0.75 );
        
        //std::cout << "initialphase = " << my_sine.initialphase << std::endl;
		
	}
    
    void testChangingPhase() {
        Jamoma::Oscillator my_sine;
        
        my_sine.frequency = 4400;
        my_sine.initialphase = 0.25;
        
        // NW: processing a few samples should result in a changing phase for internal mSync object
        Jamoma::Sample out = 0.0;
        for (int i = 0; i < 16; i++)
        {
            out = my_sine(0.0);
            //std::cout << "out = " << out << std::endl;
        }
        
        // NW: although mSync.mPhase changes, the Oscillator.initialphase does not
        mTest->TEST_ASSERT("phase parameter after processing samples", my_sine.initialphase == 0.25 );
    }
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<OscillatorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
