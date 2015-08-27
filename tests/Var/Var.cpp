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
			// Some informational posts before we get started...
			std::cout << "size of double: " << sizeof(double) << std::endl;
			std::cout << "size of TaggedValue<double>: " << sizeof(TaggedValue<double>) << std::endl;
			std::cout << "size of std::vector<double>: " << sizeof(std::vector<double>) << std::endl;
			
			std::vector<double> vec16 = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
			
			std::cout << "size of std::vector<double> len=16: " << sizeof(vec16) << std::endl;
			std::cout << "size of std::string: " << sizeof(std::string) << std::endl;
			
			std::cout << "size of long long: " << sizeof(long long) << std::endl;
			std::cout << "size of long double: " << sizeof(long double) << std::endl;
			std::cout << "size of std::vector<long double>: " << sizeof(std::vector<long double>) << std::endl;
		
			std::cout << "size of Function: " << sizeof(Function) << std::endl;
			std::cout << "size of TimePoint: " << sizeof(TimePoint) << std::endl;
			
			// Now actually run the tests
			testBasic();
		}

		
		void testBasic()
		{
			// Test setting and getting of a Function
			{
				// Simplest Case
				String			s;
				Function		f = [&s]{ s = "Hello World"; };
				Var<Function>	v = f;
				Function		f1 = v;
				
				mTest->TEST_ASSERT("s is empty", s == "");
				f1();
				mTest->TEST_ASSERT("s is has been filled-in", s == "Hello World");
			
				// Now test it using more generic version.
				VarBase&		vbr = v;
				
				// this one asserts because we request an incorrect type
				// int i = vbr;
				
				Function		f3 = vbr;
				
				s = "foo";
				f3();
				mTest->TEST_ASSERT("s is has been filled-in again", s == "Hello World");
			}
			
			
			// Test Pairs (e.g. TaggedValue)
			{
				auto						a = Tag(-6.0, Unit::db);
				Var<TaggedValue<double>>	v = a;
				VarBase						vb = a;
				TaggedValue<double>			out = v;
				
				mTest->TEST_ASSERT("TaggedValue, first item is returned correctly", mTest->compare(out.first, -6.0));
				mTest->TEST_ASSERT("TaggedValue, second item is returned correctly", out.second == Unit::db);
				
				out = vb;
				
				mTest->TEST_ASSERT("TaggedValue (value assigned from value base by value), first item is returned correctly",
								   mTest->compare(out.first, -6.0));
				mTest->TEST_ASSERT("TaggedValue (value assigned from value base by value), second item is returned correctly",
								   out.second == Unit::db);

				// normal copy assignment
				auto c = a;
				out = c;

				mTest->TEST_ASSERT("TaggedValue (value assigned from value), first item is returned correctly",
								   mTest->compare(out.first, -6.0));
				mTest->TEST_ASSERT("TaggedValue (value assigned from value), second item is returned correctly",
								   out.second == Unit::db);
				
				// the follow asserts, as it should, because the type requested doesn't match the content
				// std::pair<double, int> foo = vb;

				
				
				// TODO: passing to a parameter?
				
				
			}
			

			
			
//			Jamoma::Value val0;
//			Jamoma::Value val1 = 3.14;
//			Jamoma::Value val2(3.14);
			
//			val0 = 3.14;
			
//			bool equal = (val1 == val2);

//			mTest->TEST_ASSERT("comparison", equal);
		
//			double f1 = val1;
//			double f2 = val2;
			
//			if (f1 == f2)
//				;
			
			
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
