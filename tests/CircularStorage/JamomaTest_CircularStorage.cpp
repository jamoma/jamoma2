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

	class CircularStorageTest {
		
		UnitTest<CircularStorageTest>*	mTest;
		
	public:
		CircularStorageTest(Jamoma::UnitTest<CircularStorageTest>* test)
		: mTest(test)
		{
			testBasic();
		}

		
		void testBasic()
		{
			CircularStorage<Jamoma::Sample>		circ(8);	// 8 samples
			SampleVector						samples = {1,2,3,4,5};
			
			// write tests
			circ.write(samples);
			mTest->TEST_ASSERT("a", circ.mItems[0] == 1);
			mTest->TEST_ASSERT("b", circ.mItems[1] == 2);
			mTest->TEST_ASSERT("c", circ.mItems[2] == 3);
			mTest->TEST_ASSERT("d", circ.mItems[3] == 4);
			mTest->TEST_ASSERT("e", circ.mItems[4] == 5);
			mTest->TEST_ASSERT("f", circ.mItems[5] == 0);
			mTest->TEST_ASSERT("g", circ.mItems[6] == 0);
			mTest->TEST_ASSERT("h", circ.mItems[7] == 0);
			
			samples = {6,7,8,9,10};
			circ.write(samples);
			mTest->TEST_ASSERT("i", circ.mItems[0] == 9);
			mTest->TEST_ASSERT("j", circ.mItems[1] == 10);
			mTest->TEST_ASSERT("k", circ.mItems[2] == 3);
			mTest->TEST_ASSERT("l", circ.mItems[3] == 4);
			mTest->TEST_ASSERT("m", circ.mItems[4] == 5);
			mTest->TEST_ASSERT("n", circ.mItems[5] == 6);
			mTest->TEST_ASSERT("o", circ.mItems[6] == 7);
			mTest->TEST_ASSERT("p", circ.mItems[7] == 8);

			// read tests
			
			Jamoma::SampleVector	foo(3);
			circ.read(foo);
			mTest->TEST_ASSERT("read-00", foo[0] == 8);
			mTest->TEST_ASSERT("read-01", foo[1] == 9);
			mTest->TEST_ASSERT("read-02", foo[2] == 10);
			
			circ.read(foo); // always gets the most recent -- and nothing has changed
			mTest->TEST_ASSERT("read-10", foo[0] == 8);
			mTest->TEST_ASSERT("read-11", foo[1] == 9);
			mTest->TEST_ASSERT("read-12", foo[2] == 10);
			
			samples = {20, 21, 22};
			circ.write(samples);
			mTest->TEST_ASSERT("write-20", circ.mItems[0] == 9);
			mTest->TEST_ASSERT("write-21", circ.mItems[1] == 10);
			mTest->TEST_ASSERT("write-22", circ.mItems[2] == 20);
			mTest->TEST_ASSERT("write-23", circ.mItems[3] == 21);
			mTest->TEST_ASSERT("write-24", circ.mItems[4] == 22);
			mTest->TEST_ASSERT("write-25", circ.mItems[5] == 6);
			mTest->TEST_ASSERT("write-26", circ.mItems[6] == 7);
			mTest->TEST_ASSERT("write-27", circ.mItems[7] == 8);
			
			circ.read(foo);
			mTest->TEST_ASSERT("read-20", foo[0] == 20);
			mTest->TEST_ASSERT("read-21", foo[1] == 21);
			mTest->TEST_ASSERT("read-22", foo[2] == 22);
			
			samples = {100, 101, 102};
			circ.write(samples);
			mTest->TEST_ASSERT("write-30", circ.mItems[0] == 9);
			mTest->TEST_ASSERT("write-31", circ.mItems[1] == 10);
			mTest->TEST_ASSERT("write-32", circ.mItems[2] == 20);
			mTest->TEST_ASSERT("write-33", circ.mItems[3] == 21);
			mTest->TEST_ASSERT("write-34", circ.mItems[4] == 22);
			mTest->TEST_ASSERT("write-35", circ.mItems[5] == 100);
			mTest->TEST_ASSERT("write-36", circ.mItems[6] == 101);
			mTest->TEST_ASSERT("write-37", circ.mItems[7] == 102);

			circ.read(foo);
			mTest->TEST_ASSERT("read-30", foo[0] == 100);
			mTest->TEST_ASSERT("read-31", foo[1] == 101);
			mTest->TEST_ASSERT("read-32", foo[2] == 102);
			
			foo.resize(5);
			mTest->TEST_ASSERT("write-40", circ.mItems[0] == 9);
			mTest->TEST_ASSERT("write-41", circ.mItems[1] == 10);
			mTest->TEST_ASSERT("write-42", circ.mItems[2] == 20);
			mTest->TEST_ASSERT("write-43", circ.mItems[3] == 21);
			mTest->TEST_ASSERT("write-44", circ.mItems[4] == 22);
			
			circ.read(foo);
			mTest->TEST_ASSERT("write-42", circ.mItems[2] == 20);
			mTest->TEST_ASSERT("write-43", circ.mItems[3] == 21);
			mTest->TEST_ASSERT("write-44", circ.mItems[4] == 22);
		}
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::CircularStorageTest>	aUnitTestInstance;
	return 0;
}
