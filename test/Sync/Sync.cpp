/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Sync class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"

namespace Jamoma {

	class SyncTest {
		
		UnitTest<SyncTest>*	mTest;
		
	public:
		SyncTest(Jamoma::UnitTest<SyncTest>* test)
		: mTest(test)
		{
			testParameterSetting();
			testOutputValues();
            testPhaseWrapping();
            testOutputAcrossMultipleVectors();
		}

		
		void testParameterSetting()
		{
			Jamoma::Sync	s;
			
			using namespace Dataspace;
			using namespace std;

			// Gain parameter (gain dataspace)
			
			s.gain = make_pair(0.25, Unit::linearGain);
			mTest->TEST_ASSERT("setting gain param linearly", mTest->compare( (double)s.gain, 0.25) );

			s.gain = make_pair(-6.0, Unit::db);
			mTest->TEST_ASSERT("setting gain param in db", mTest->compare( (double)s.gain, 0.50118723362727224) );

			s.gain = make_pair(110.0, Unit::midiGain);
			mTest->TEST_ASSERT("setting gain param with midi", mTest->compare( (double)s.gain, 1.5826306885735968) );
			
			// initialphase parameter (range wrapping)
			s.initialphase = 0.25;
			mTest->TEST_ASSERT("setting initialphase param within range", mTest->compare( (double)s.initialphase, 0.25) );
		
			s.initialphase = 1.3;
			mTest->TEST_ASSERT("setting initialphase param over range", mTest->compare( (double)s.initialphase, 0.3) );
			
			s.initialphase = 2.45;
			mTest->TEST_ASSERT("setting initialphase param way over range", mTest->compare( (double)s.initialphase, 0.45) );
			
			s.initialphase = -1.3;
			mTest->TEST_ASSERT("setting initialphase param under range", mTest->compare( (double)s.initialphase, 0.7) );
			
			// Frequency parameter (range folding)
			
			s.sampleRate = 96000;
			
			s.frequency = 1000.0;
			mTest->TEST_ASSERT("setting frequency param within range", mTest->compare( (double)s.frequency, 1000.0) );

			s.frequency = 50000.0;
			mTest->TEST_ASSERT("setting frequency param way above range 1", mTest->compare( (double)s.frequency, 46000.0) );

			s.frequency = 98000.0;
			mTest->TEST_ASSERT("setting frequency param way above range 2", mTest->compare( (double)s.frequency, -2000.0) );
			
			s.frequency = -2000.0;
			mTest->TEST_ASSERT("setting frequency param below range", mTest->compare( (double)s.frequency, -2000.0) );

		}
        
        void testOutputValues()
        {
            
            Jamoma::Sync my_sync;
            
            my_sync.channelCount = 1;
            my_sync.frameCount = 64;
            
            // settings group 1
            my_sync.sampleRate = 44100;
            my_sync.initialphase = 0.0;
            my_sync.frequency = 100.0;
            
            auto out_samples = my_sync();
            
            // The following output was generated using the Octave code
            // in SyncTargetOutput.m by NW with the following starting values:
            // frequency = 100.0;
            // initialPhase = 0.0;
            // sampleRate = 44100.0;
            Jamoma::SampleVector expectedOutput1 = {
                0,
                0.002267573696145125,
                0.00453514739229025,
                0.006802721088435375,
                0.009070294784580499,
                0.01133786848072562,
                0.01360544217687075,
                0.01587301587301587,
                0.018140589569161,
                0.02040816326530612,
                0.02267573696145125,
                0.02494331065759638,
                0.0272108843537415,
                0.02947845804988663,
                0.03174603174603175,
                0.03401360544217687,
                0.036281179138322,
                0.03854875283446712,
                0.04081632653061224,
                0.04308390022675736,
                0.04535147392290249,
                0.04761904761904761,
                0.04988662131519273,
                0.05215419501133785,
                0.05442176870748298,
                0.0566893424036281,
                0.05895691609977322,
                0.06122448979591835,
                0.06349206349206347,
                0.0657596371882086,
                0.06802721088435372,
                0.07029478458049884,
                0.07256235827664397,
                0.07482993197278909,
                0.07709750566893421,
                0.07936507936507933,
                0.08163265306122446,
                0.08390022675736958, 
                0.0861678004535147, 
                0.08843537414965982, 
                0.09070294784580495, 
                0.09297052154195007, 
                0.09523809523809519, 
                0.09750566893424031, 
                0.09977324263038544, 
                0.1020408163265306, 
                0.1043083900226757, 
                0.1065759637188208, 
                0.1088435374149659, 
                0.111111111111111, 
                0.1133786848072562, 
                0.1156462585034013, 
                0.1179138321995464, 
                0.1201814058956915, 
                0.1224489795918367, 
                0.1247165532879818, 
                0.1269841269841269, 
                0.1292517006802721, 
                0.1315192743764172, 
                0.1337868480725623, 
                0.1360544217687075, 
                0.1383219954648526, 
                0.1405895691609977, 
                0.1428571428571429
            };
            
            int badSampleCount = 0;
            Jamoma::Sample temp = 0.0;
            Jamoma::Sample tempExpected = 0.0;
            
            for (int i = 0; i < expectedOutput1.size(); i++) {
                temp = out_samples[0][0][i];
                tempExpected = expectedOutput1[i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            std::cout << "output from my_sync has " << badSampleCount << " bad samples" << std::endl;
            mTest->TEST_ASSERT("settings group 1 produces expected output samples", badSampleCount == 0);
            
            // settings group 2
            my_sync.sampleRate = 96000;
            my_sync.initialphase = 0.25;
            my_sync.frequency = 1.0;
            
            out_samples = my_sync();
            
            // The following output was generated using the Octave code
            // in SyncTargetOutput.m by NW with the following starting values:
            // frequency = 1.0;
            // initialPhase = 0.25;
            // sampleRate = 96000.0;
            Jamoma::SampleVector expectedOutput2 = {
                0.25,
                0.2500104166666667,
                0.2500208333333334,
                0.25003125,
                0.2500416666666667,
                0.2500520833333334,
                0.2500625000000001,
                0.2500729166666668,
                0.2500833333333334,
                0.2500937500000001,
                0.2501041666666668,
                0.2501145833333335,
                0.2501250000000002,
                0.2501354166666668,
                0.2501458333333335,
                0.2501562500000002,
                0.2501666666666669,
                0.2501770833333335,
                0.2501875000000002,
                0.2501979166666669,
                0.2502083333333336,
                0.2502187500000003,
                0.2502291666666669,
                0.2502395833333336,
                0.2502500000000003,
                0.250260416666667,
                0.2502708333333337,
                0.2502812500000003,
                0.250291666666667,
                0.2503020833333337,
                0.2503125000000004,
                0.2503229166666671,
                0.2503333333333337,
                0.2503437500000004,
                0.2503541666666671,
                0.2503645833333338,
                0.2503750000000005,
                0.2503854166666671,
                0.2503958333333338,
                0.2504062500000005,
                0.2504166666666672,
                0.2504270833333339, 
                0.2504375000000005, 
                0.2504479166666672, 
                0.2504583333333339, 
                0.2504687500000006, 
                0.2504791666666673, 
                0.2504895833333339, 
                0.2505000000000006, 
                0.2505104166666673, 
                0.250520833333334, 
                0.2505312500000006, 
                0.2505416666666673, 
                0.250552083333334, 
                0.2505625000000007, 
                0.2505729166666674, 
                0.250583333333334, 
                0.2505937500000007, 
                0.2506041666666674, 
                0.2506145833333341, 
                0.2506250000000008, 
                0.2506354166666674, 
                0.2506458333333341, 
                0.2506562500000008
            };
            
            // reset variables
            badSampleCount = 0;
            temp = 0.0;
            tempExpected = 0.0;
            
            for (int i = 0; i < expectedOutput2.size(); i++) {
                temp = out_samples[0][0][i];
                tempExpected = expectedOutput2[i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            std::cout << "output from my_sync has " << badSampleCount << " bad samples" << std::endl;
            mTest->TEST_ASSERT("settings group 2 produces expected output samples", badSampleCount == 0);
            
        }
        
        void testPhaseWrapping()
        {
            
            Jamoma::Sync my_sync;
            
            my_sync.channelCount = 1;
            my_sync.frameCount = 64;
            
            // NEGATIVE STEPS WRAPPING THOUGH 0.0

            my_sync.sampleRate = 48000;
            my_sync.initialphase = 0.1;
            my_sync.frequency = -2000.0;
            
            auto out_samples = my_sync();
            
            // The following output was generated using the Octave code
            // in SyncTargetOutput.m by NW with the following starting values:
            // frequency = -2000.0;
            // initialPhase = 0.1;
            // sampleRate = 48000.0;
            Jamoma::SampleVector expectedOutput3 = {
                0.1,
                0.05833333333333334,
                0.01666666666666668,
                0.975,
                0.9333333333333333,
                0.8916666666666667,
                0.8500000000000001,
                0.8083333333333335,
                0.7666666666666668,
                0.7250000000000002,
                0.6833333333333336,
                0.6416666666666669,
                0.6000000000000003,
                0.5583333333333337,
                0.5166666666666671,
                0.4750000000000004,
                0.4333333333333337,
                0.391666666666667,
                0.3500000000000003,
                0.3083333333333336,
                0.2666666666666669,
                0.2250000000000003,
                0.1833333333333336,
                0.141666666666667,
                0.1000000000000003,
                0.05833333333333365,
                0.01666666666666698,
                0.9750000000000003,
                0.9333333333333337,
                0.8916666666666671,
                0.8500000000000004,
                0.8083333333333338,
                0.7666666666666672,
                0.7250000000000005,
                0.6833333333333339,
                0.6416666666666673,
                0.6000000000000006,
                0.558333333333334,
                0.5166666666666674,
                0.4750000000000007,
                0.433333333333334,
                0.3916666666666673, 
                0.3500000000000006, 
                0.308333333333334, 
                0.2666666666666673, 
                0.2250000000000006, 
                0.183333333333334, 
                0.1416666666666673, 
                0.1000000000000006, 
                0.05833333333333398, 
                0.01666666666666732, 
                0.9750000000000006, 
                0.933333333333334, 
                0.8916666666666674, 
                0.8500000000000008, 
                0.8083333333333341, 
                0.7666666666666675, 
                0.7250000000000009, 
                0.6833333333333342, 
                0.6416666666666676, 
                0.600000000000001, 
                0.5583333333333343, 
                0.5166666666666677, 
                0.475000000000001
            };
            
            int badSampleCount = 0;
            Jamoma::Sample temp = 0.0;
            Jamoma::Sample tempExpected = 0.0;
            
            for (int i = 0; i < expectedOutput3.size(); i++) {
                temp = out_samples[0][0][i];
                tempExpected = expectedOutput3[i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            std::cout << "output from my_sync has " << badSampleCount << " bad samples" << std::endl;
            mTest->TEST_ASSERT("negative frequency wrapping test produces expected samples", badSampleCount == 0);
            
            // POSITIVE STEPS WRAPPING THOUGH 1.0

            my_sync.sampleRate = 22050;
            my_sync.initialphase = 0.4;
            my_sync.frequency = 3000.0;
            
            out_samples = my_sync();
        
            // The following output was generated using the Octave code
            // in SyncTargetOutput.m by NW with the following starting values:
            // frequency = 3000.0;
            // initialPhase = 0.4;
            // sampleRate = 22050.0;
            Jamoma::SampleVector expectedOutput4 = {
                0.4,
                0.5360544217687075,
                0.6721088435374151,
                0.8081632653061226,
                0.9442176870748301,
                0.08027210884353764,
                0.2163265306122451,
                0.3523809523809526,
                0.4884353741496601,
                0.6244897959183676,
                0.7605442176870751,
                0.8965986394557827,
                0.03265306122449019,
                0.1687074829931977,
                0.3047619047619052,
                0.4408163265306126,
                0.5768707482993202,
                0.7129251700680277,
                0.8489795918367352,
                0.9850340136054427,
                0.1210884353741501,
                0.2571428571428577,
                0.3931972789115652,
                0.5292517006802727,
                0.6653061224489802,
                0.8013605442176878,
                0.9374149659863953,
                0.0734693877551027,
                0.2095238095238102,
                0.3455782312925177,
                0.4816326530612252,
                0.6176870748299327,
                0.7537414965986402,
                0.8897959183673477,
                0.02585034013605525,
                0.1619047619047627,
                0.2979591836734702,
                0.4340136054421777, 
                0.5700680272108852, 
                0.7061224489795928, 
                0.8421768707483003, 
                0.9782312925170078, 
                0.1142857142857152, 
                0.2503401360544227, 
                0.3863945578231303, 
                0.5224489795918378, 
                0.6585034013605453, 
                0.7945578231292528, 
                0.9306122448979604, 
                0.06666666666666776, 
                0.2027210884353753, 
                0.3387755102040828, 
                0.4748299319727902, 
                0.6108843537414977, 
                0.7469387755102053, 
                0.8829931972789128, 
                0.01904761904762031, 
                0.1551020408163278, 
                0.2911564625850353, 
                0.4272108843537428, 
                0.5632653061224503, 
                0.6993197278911578, 
                0.8353741496598653,
                0.9714285714285729
            };
            
            // reset variables
            badSampleCount = 0;
            temp = 0.0;
            tempExpected = 0.0;
            
            for (int i = 0; i < expectedOutput4.size(); i++) {
                temp = out_samples[0][0][i];
                tempExpected = expectedOutput4[i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            std::cout << "output from my_sync has " << badSampleCount << " bad samples" << std::endl;
            mTest->TEST_ASSERT("positive frequency wrapping test produces expected samples", badSampleCount == 0);
            
        }
        
        void testOutputAcrossMultipleVectors() {
            
            Jamoma::Sync my_sync16;
            
            my_sync16.channelCount = 1;
            my_sync16.frameCount = 16;
            
            my_sync16.sampleRate = 48000;
            my_sync16.initialphase = 0.0;
            my_sync16.frequency = 1.0;
            
            // store four vectors for testing
            Jamoma::SampleBundle out_samples16_1 = my_sync16();
            Jamoma::SampleBundle out_samples16_2 = my_sync16();
            Jamoma::SampleBundle out_samples16_3 = my_sync16();
            Jamoma::SampleBundle out_samples16_4 = my_sync16();
            
            // test is really about consistency,
            // so we will use Jamoma to generate target not Octave
            Jamoma::Sync my_sync64;
            
            my_sync64.channelCount = 1;
            my_sync64.frameCount = 64;
            
            my_sync64.sampleRate = 48000;
            my_sync64.initialphase = 0.0;
            my_sync64.frequency = 1.0;
            
            // store four vectors for testing
            Jamoma::SampleBundle out_samples64 = my_sync64();
            
            int badSampleCount = 0;
            Jamoma::Sample temp = 0.0;
            Jamoma::Sample tempExpected = 0.0;
            
            for (int i = 0; i < out_samples16_1[0].size(); i++) {
                temp = out_samples64[0][i];
                tempExpected = out_samples16_1[0][i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            for (int i = 16; i < out_samples16_2[0].size(); i++) {
                temp = out_samples64[0][i+16];
                tempExpected = out_samples16_2[0][i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            for (int i = 32; i < out_samples16_3[0].size(); i++) {
                temp = out_samples64[0][i+32];
                tempExpected = out_samples16_3[0][i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            for (int i = 48; i < out_samples16_4[0].size(); i++) {
                temp = out_samples64[0][i+48];
                tempExpected = out_samples16_4[0][i];
                if (! mTest->compare(temp, tempExpected, true, 8) ) {
                    badSampleCount++;
                    std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
                }
            }
            
            std::cout << "output from my_sync16 has " << badSampleCount << " bad samples" << std::endl;
            mTest->TEST_ASSERT("out across multiple vectors produces expected samples", badSampleCount == 0);
            
            
        }
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::SyncTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
