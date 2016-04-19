/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the SampleBuffer class
 
	@author		Nathan Wolek, Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"

namespace Jamoma {

	class SampleBufferTest {
		
		UnitTest<SampleBufferTest>*	mTest;
		
	public:
		SampleBufferTest(Jamoma::UnitTest<SampleBufferTest>* test)
		: mTest(test)
		{
			//testBasic();
		}

		/*
		void testBasic()
		{
			Jamoma::SampleBuffer	my_samples(1, 4);
			
			my_samples.fill(1.0);
			
			int badSampleCount = 0;
			Jamoma::Sample temp = 0.0;
			Jamoma::Sample tempExpected = 1.0;

			for (int i = 0; i < my_samples.frameCount(); i++)
			{
				temp = my_samples[0][i];
				if (mTest->compare(temp, tempExpected) ) {
					badSampleCount++;
				}
			}
			
			mTest->TEST_ASSERT("filled with ones", badSampleCount == 0);
		}
         */
        
    };

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::SampleBufferTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
