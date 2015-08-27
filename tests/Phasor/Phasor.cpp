/** @file
	@ingroup jamoma2
 
	@brief Unit test for the Gain class
 
	@author Timothy Place
 
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
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
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::PhasorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
