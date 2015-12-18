/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Limiter class
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class LimiterTest {
	
	Jamoma::UnitTest<LimiterTest>*	mTest;
	
public:
	LimiterTest(Jamoma::UnitTest<LimiterTest>* test)
	: mTest(test)
	{
		testImpulseResponse();
	}

	
	void testImpulseResponse()
	{
		Jamoma::Limiter my_limiter;

		using namespace std;
		using namespace Jamoma;
		using namespace Dataspace;

		my_limiter.threshold = make_pair(-6.0, Unit::db);
		
		// TODO: check response against Jamoma1 implementation
		
		mTest->TEST_ASSERT("has legit tests", false);
		
	}

};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<LimiterTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
