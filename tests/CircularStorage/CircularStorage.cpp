/** @file
	@ingroup 	jamoma2
 
	@brief		Unit test for the Dcblocker class
 
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

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
			testDelay();
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
		
		
		void testDelay()
		{
			CircularStorage<Jamoma::Sample>		circ(16);		// storage for 16 samples
			SampleVector						samples(4);		// vector size of 4
			SampleVector						output(4);		// ...
			
			// default is that delay will be the size of the capacity of the buffer (16 samples)
			
			// we read from the delay line *before* writing to it
			
			circ.tail(output);
			mTest->TEST_ASSERT("out-00", output[0]==0 && output[1]==0 && output[2]==0 && output[3]==0);
			samples = {1,2,3,4};
			circ.write(samples);

			circ.tail(output);
			mTest->TEST_ASSERT("out-01", output[0]==0 && output[1]==0 && output[2]==0 && output[3]==0);
			samples = {5,6,7,8};
			circ.write(samples);
			
			circ.tail(output);
			mTest->TEST_ASSERT("out-02", output[0]==0 && output[1]==0 && output[2]==0 && output[3]==0);
			samples = {9,10,11,12};
			circ.write(samples);
			
			circ.tail(output);
			mTest->TEST_ASSERT("out-03", output[0]==0 && output[1]==0 && output[2]==0 && output[3]==0);
			samples = {13,14,15,16};
			circ.write(samples);
			
			circ.tail(output);
			// tail should produce what happened 16 samples ago: 1,2,3,4
			mTest->TEST_ASSERT("out-04", output[0]==1 && output[1]==2 && output[2]==3 && output[3]==4);
			samples = {17,18,19,20};
			circ.write(samples);
			
			circ.tail(output);
			// tail should produce what happened 16 samples ago: 5,6,7,8
			mTest->TEST_ASSERT("out-05", output[0]==5 && output[1]==6 && output[2]==7 && output[3]==8);
			samples = {21,22,23,24};
			circ.write(samples);
			
			
			// Change delay time!
			
			circ.resize(10);
			
			circ.tail(output);
			// if tail produced what happened 10 samples ago it would be: 15,16,17,18
			// but we just shortened the delay, which means some samples are going to get dropped
			mTest->TEST_ASSERT("out-06", output[0]==9 && output[1]==10 && output[2]==17 && output[3]==18);
			samples = {25,26,27,28};
			circ.write(samples);
			
			circ.tail(output);
			// tail should produce what happened 10 samples ago: 19,20,21,22
			mTest->TEST_ASSERT("out-07", output[0]==19 && output[1]==20 && output[2]==21 && output[3]==22);
			samples = {29,30,31,32};
			circ.write(samples);
		}

	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::CircularStorageTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
