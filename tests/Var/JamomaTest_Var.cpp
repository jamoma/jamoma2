/** @file
	@ingroup jamoma2
 
	@brief Unit test for the Dcblocker class
 
	@author Timothy Place, Nathan Wolek
 
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#include "Jamoma.h"

namespace Jamoma {

	class VarTest {
		
		UnitTest<VarTest>*	mTest;
		
	public:
		VarTest(Jamoma::UnitTest<VarTest>* test)
		: mTest(test)
		{
			testBasic();
		}

		
		void testBasic()
		{
			
			Jamoma::Value val0;
			Jamoma::Value val1 = 3.14;
			Jamoma::Value val2(3.14);
			
			val0 = 3.14;
			
//			bool equal = (val1 == val2);

//			mTest->TEST_ASSERT("comparison", equal);
		
			double f1 = val1;
			double f2 = val2;
			
			if (f1 == f2)
				;
			
			
/*
			Jamoma::Var	v0;	// empty -- how do we test it?
			
			
			Jamoma::Var v1 = {3.14};
			
			
			Jamoma::Var v2(3.14); // should yield the same result as the above
			
			
			f1 = v1;
			f2 = v2;
			
			equal = (v1 == v2);
			
			
			mTest->TEST_ASSERT("comparison", equal);
*/
			
			
		}
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::VarTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
