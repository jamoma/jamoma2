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
			
			Jamoma::SampleVector	head_samples(3);
			Jamoma::SampleVector	tail_samples(3);
			
			circ.head(head_samples);
			mTest->TEST_ASSERT("read-00", head_samples[0] == 8);
			mTest->TEST_ASSERT("read-01", head_samples[1] == 9);
			mTest->TEST_ASSERT("read-02", head_samples[2] == 10);

			circ.tail(tail_samples);
			mTest->TEST_ASSERT("tail-00", tail_samples[0] == 3);
			mTest->TEST_ASSERT("tail-01", tail_samples[1] == 4);
			mTest->TEST_ASSERT("tail-02", tail_samples[2] == 5);

			
			circ.head(head_samples); // always gets the most recent -- and nothing has changed
			mTest->TEST_ASSERT("read-10", head_samples[0] == 8);
			mTest->TEST_ASSERT("read-11", head_samples[1] == 9);
			mTest->TEST_ASSERT("read-12", head_samples[2] == 10);

			circ.tail(tail_samples); // always gets the oldest -- and nothing has changed
			mTest->TEST_ASSERT("tail-10", tail_samples[0] == 3);
			mTest->TEST_ASSERT("tail-11", tail_samples[1] == 4);
			mTest->TEST_ASSERT("tail-12", tail_samples[2] == 5);
			

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
			
			circ.head(head_samples);
			mTest->TEST_ASSERT("read-20", head_samples[0] == 20);
			mTest->TEST_ASSERT("read-21", head_samples[1] == 21);
			mTest->TEST_ASSERT("read-22", head_samples[2] == 22);
	
			circ.tail(tail_samples);
			mTest->TEST_ASSERT("tail-20", tail_samples[0] == 6);
			mTest->TEST_ASSERT("tail-21", tail_samples[1] == 7);
			mTest->TEST_ASSERT("tail-22", tail_samples[2] == 8);

			
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

			circ.head(head_samples);
			mTest->TEST_ASSERT("read-30", head_samples[0] == 100);
			mTest->TEST_ASSERT("read-31", head_samples[1] == 101);
			mTest->TEST_ASSERT("read-32", head_samples[2] == 102);

			circ.tail(tail_samples);
			mTest->TEST_ASSERT("tail-30", tail_samples[0] == 9);
			mTest->TEST_ASSERT("tail-31", tail_samples[1] == 10);
			mTest->TEST_ASSERT("tail-32", tail_samples[2] == 20);

			
			head_samples.resize(5);
			tail_samples.resize(5);
			mTest->TEST_ASSERT("write-40", circ.mItems[0] == 9);
			mTest->TEST_ASSERT("write-41", circ.mItems[1] == 10);
			mTest->TEST_ASSERT("write-42", circ.mItems[2] == 20);
			mTest->TEST_ASSERT("write-43", circ.mItems[3] == 21);
			mTest->TEST_ASSERT("write-44", circ.mItems[4] == 22);
			
			circ.head(head_samples);
			mTest->TEST_ASSERT("head-50", head_samples[0] == 21);
			mTest->TEST_ASSERT("head-51", head_samples[1] == 22);
			mTest->TEST_ASSERT("head-52", head_samples[2] == 100);
			mTest->TEST_ASSERT("head-53", head_samples[3] == 101);
			mTest->TEST_ASSERT("head-54", head_samples[4] == 102);
			
			circ.tail(tail_samples);
			mTest->TEST_ASSERT("tail-50", tail_samples[0] == 9);
			mTest->TEST_ASSERT("tail-51", tail_samples[1] == 10);
			mTest->TEST_ASSERT("tail-52", tail_samples[2] == 20);
			mTest->TEST_ASSERT("tail-53", tail_samples[3] == 21);
			mTest->TEST_ASSERT("tail-54", tail_samples[4] == 22);
		}
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::CircularStorageTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
