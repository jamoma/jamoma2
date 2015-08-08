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

	class DataspaceTest {
		
		UnitTest<DataspaceTest>*	mTest;
		
	public:
		DataspaceTest(Jamoma::UnitTest<DataspaceTest>* test)
		: mTest(test)
		{
			testGain();
		}

		
		void testGain()
		{
			// Dataspace Test
			double y = 0;
			
			
			// Gain: conversions to linear
			Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::linear>		linearGainConverter;
			
			y = linearGainConverter(0.5);
			mTest->TEST_ASSERT("unspecified unit is assumed to be the native unit (linear)", mTest->compare(y, 0.5));
			
			y = linearGainConverter(-6, Dataspace::GainUnit::db);
			mTest->TEST_ASSERT("db unit specified as enum", mTest->compare(y, 0.50118723362727224));
			
			y = linearGainConverter(-12, "db");
			// TODO: test
			mTest->TEST_ASSERT("db unit specified as string", mTest->compare(y, 0.25118864315095796));
			
			
			// Gain: conversions to db
			Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::db>		dbGainConverter;
			
			y = dbGainConverter(0.5);
			mTest->TEST_ASSERT("unspecified unit is assumed to be the native unit (db)", mTest->compare(y, 0.5));
			
			y = dbGainConverter(2.0, Dataspace::GainUnit::linear);
			mTest->TEST_ASSERT("linear-to-db", mTest->compare(y, 6.0205999132796242));
			
			y = dbGainConverter(100.0, Dataspace::GainUnit::midi);
			mTest->TEST_ASSERT("midi-to-db using enum unit", mTest->compare(y, 0.0));
			
			y = dbGainConverter(50, "midi");
			mTest->TEST_ASSERT("midi-to-db using string unit", mTest->compare(y, -28.999923402717513));
			
		}
		
		
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::DataspaceTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
