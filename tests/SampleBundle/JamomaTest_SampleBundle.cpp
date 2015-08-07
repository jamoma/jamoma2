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

	class SampleBundleTest {
		
		UnitTest<SampleBundleTest>*	mTest;
		
	public:
		SampleBundleTest(Jamoma::UnitTest<SampleBundleTest>* test)
		: mTest(test)
		{
			testBasic();
		}

		
		void testBasic()
		{
			// gain -- single sample
			
			Jamoma::Gain	my_gain;
			Jamoma::Sample	x = 1.0;
			Jamoma::Sample	y = 0.0;
			
			my_gain.gain = 0.5;
			y = my_gain(x);
			
			mTest->TEST_ASSERT("single sample gain", mTest->compare(y, 0.5));
			
			
			// gain -- vector
			
			Jamoma::SampleBundle	in_samples(2, 8);
			
			in_samples.fill(1.0);
			auto out_samples = my_gain(in_samples);
			
			mTest->TEST_ASSERT("vector sample gain left 0", mTest->compare(out_samples[0][0][0], 0.5));
			mTest->TEST_ASSERT("vector sample gain right 0", mTest->compare(out_samples[0][1][0], 0.5));
			mTest->TEST_ASSERT("vector sample gain left 1", mTest->compare(out_samples[0][0][1], 0.5));
			mTest->TEST_ASSERT("vector sample gain right 2", mTest->compare(out_samples[0][1][1], 0.5));

			my_gain.gain = 0.25;
			in_samples = out_samples;
			out_samples = my_gain(in_samples);
			
			mTest->TEST_ASSERT("vector b sample gain left 0", mTest->compare(out_samples[0][0][0], 0.125));
			mTest->TEST_ASSERT("vector b sample gain right 0", mTest->compare(out_samples[0][1][0], 0.125));
			mTest->TEST_ASSERT("vector b sample gain left 1", mTest->compare(out_samples[0][0][1], 0.125));
			mTest->TEST_ASSERT("vector b sample gain right 2", mTest->compare(out_samples[0][1][1], 0.125));
			
			// samplebundle
			
			auto bar = in_samples[0][0];
			mTest->TEST_ASSERT("in_sample casting operator", mTest->compare(bar, 0.5));
			
			in_samples[0][0] = 2.0;
			auto foo = in_samples[0][0];
			mTest->TEST_ASSERT("setting and getting", mTest->compare(foo, 2.0));
		}
	};

} // namespace Jamoma


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<Jamoma::SampleBundleTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
