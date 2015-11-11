/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Gain class
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"

namespace Jamoma {

	class PhasorTest {
		
		UnitTest<PhasorTest>*	mTest;
		
	public:
		PhasorTest(Jamoma::UnitTest<PhasorTest>* test)
		: mTest(test)
		{
			testParameterSetting();
			testOutputValues();
		}
		
		
		void testOutputValues()
		{
			// TODO: implement
		}

		
		void testParameterSetting()
		{
			Jamoma::Phasor	p;
			
			using namespace Dataspace;
			using namespace std;

			// Gain parameter (gain dataspace)
			
			p.gain = make_pair(0.25, Unit::linearGain);
			mTest->TEST_ASSERT("setting gain param linearly", mTest->compare( (double)p.gain, 0.25) );

			p.gain = make_pair(-6.0, Unit::db);
			mTest->TEST_ASSERT("setting gain param in db", mTest->compare( (double)p.gain, 0.50118723362727224) );

			p.gain = make_pair(110.0, Unit::midiGain);
			mTest->TEST_ASSERT("setting gain param with midi", mTest->compare( (double)p.gain, 1.5826306885735968) );
			
			// Phase parameter (range wrapping)
			p.phase = 0.25;
			mTest->TEST_ASSERT("setting phase param within range", mTest->compare( (double)p.phase, 0.25) );
		
			p.phase = 1.3;
			mTest->TEST_ASSERT("setting phase param over range", mTest->compare( (double)p.phase, 0.3) );
			
			p.phase = 2.45;
			mTest->TEST_ASSERT("setting phase param way over range", mTest->compare( (double)p.phase, 0.45) );
			
			p.phase = -1.3;
			mTest->TEST_ASSERT("setting phase param under range", mTest->compare( (double)p.phase, 0.7) );
			
			// Frequency parameter (range folding)
			
			p.sampleRate = 96000;
			
			p.frequency = 1000.0;
			mTest->TEST_ASSERT("setting frequency param within range", mTest->compare( (double)p.frequency, 1000.0) );

			p.frequency = 50000.0;
			mTest->TEST_ASSERT("setting frequency param way above range", mTest->compare( (double)p.frequency, 46000.0) );

			p.frequency = 98000.0;
			mTest->TEST_ASSERT("setting frequency param way above range", mTest->compare( (double)p.frequency, 2000.0) );
			
			p.frequency = -2000.0;
			mTest->TEST_ASSERT("setting frequency param below range", mTest->compare( (double)p.frequency, 2000.0) );

		}
        
        void testPhasorOutput()
        {
            
            // The following output was generated using the Octave code
            // in PhasorTargetOutput.m by NW with the following starting values:
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
            
            // The following output was generated using the Octave code
            // in PhasorTargetOutput.m by NW with the following starting values:
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
        }
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::PhasorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
