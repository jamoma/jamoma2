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
        testOutput();
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
        
        // Gain parameter (gain dataspace)
        // NW: gain is no longer a parameter of Sync, so tests need to move.
        // maybe up to the oscillator object?
        
        using namespace Dataspace;
        using namespace std;
        
        my_sine.gain = make_pair(0.25, Unit::linearGain);
        mTest->TEST_ASSERT("setting gain param linearly", mTest->compare( (double)my_sine.gain, 0.25) );
        
        my_sine.gain = make_pair(-6.0, Unit::db);
        mTest->TEST_ASSERT("setting gain param in db", mTest->compare( (double)my_sine.gain, 0.50118723362727224) );
        
        my_sine.gain = make_pair(110.0, Unit::midiGain);
        mTest->TEST_ASSERT("setting gain param with midi", mTest->compare( (double)my_sine.gain, 1.5826306885735968) );
		
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
    
    void testOutput() {
        Jamoma::Oscillator my_sine;
        
        my_sine.channelCount = 1;
        my_sine.frameCount = 64;
        
        my_sine.frequency = 440;
        my_sine.initialphase = 0.0;
        
        auto out_samples = my_sine();
        
        // The following output was generated using the Octave code
        // in OscillatorTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputSine440 = {
            0,
            0.02879395236826347,
            0.05756402695956728,
            0.08628636579792337,
            0.1149371504928666,
            0.1434926219911793,
            0.1719291002794096,
            0.2002230040208447,
            0.2283508701106558,
            0.2562893731329967,
            0.2840153447039227,
            0.3115057926840882,
            0.3387379202452915,
            0.3656891447750544,
            0.3923371166035615,
            0.4186597375374281,
            0.4446351791849275,
            0.4702419010574822,
            0.4954586684324075,
            0.5202645699620939,
            0.544639035015027,
            0.5685618507342638,
            0.5920131787992193,
            0.6149735718768641,
            0.6374239897486895,
            0.6593458151000686,
            0.6807208689589176,
            0.7015314257708554,
            0.7217602280983618,
            0.7413905009317419,
            0.7604059656000306,
            0.7787908532703037,
            0.7965299180241959,
            0.8136084495007867,
            0.8300122850953671,
            0.845727821703973,
            0.8607420270039432,
            0.875042450261152,
            0.8886172326549484,
            0.9014551171122454,
            0.9135454576426005,
            0.9248782281665493,
            0.935444030829867,
            0.9452341037968679,
            0.9542403285162766,
            0.9624552364536471,
            0.9698720152847465,
            0.9764845145447685,
            0.9822872507286885,
            0.9872754118385363,
            0.9914448613738103,
            0.9947921417617264,
            0.997314477224458,
            0.9990097760809874,
            0.9998766324816606,
            0.999914327574007,
            0.9991228300988584,
            0.9975027964162702,
            0.9950555699612265,
            0.9917831801295779,
            0.987688340595138,
            0.9827744470593316,
            0.977045574435264,
            0.9705064734685428
        };
        
        int badSampleCount = 0;
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double difference = 0.0;
        
        for (int i = 0; i < expectedOutputSine440.size(); i++) {
            temp = out_samples[0][0][i];
            tempExpected = expectedOutputSine440[i];
            difference = std::fabs(temp - tempExpected);
            
            // NW: using a slightly different comparison here
            // since the target values were generated using sine function directly, not via wavetable
            // TODO: develop more exact expectedOutputSine440 array
            if ( difference > 0.0000001 ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << difference << std::endl;
            }
        }
        
        std::cout << "output from my_sine has " << badSampleCount << " bad samples" << std::endl;
        mTest->TEST_ASSERT("sine 440 produces expected output samples", badSampleCount == 0);
    }
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<OscillatorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
