/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Delay class
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class DelayTest {
	
	Jamoma::UnitTest<DelayTest>*	mTest;
	
public:
	DelayTest(Jamoma::UnitTest<DelayTest>* test)
	: mTest(test)
	{
		testDelayGreaterThanOneVectorSize();
		
		testDelayGreaterThanOneVectorSize2();
		testDelayLessThanOneVectorSize();
		
		testDelaySingleSample();
	}

	
	void testDelayGreaterThanOneVectorSize()
	{
		Jamoma::SampleBundle zero(2, 64);
		
		Jamoma::UnitImpulse impulse;
		impulse.channelCount = 2;
		impulse.frameCount = 64;

		Jamoma::Delay my_delay;
		my_delay.sampleRate = 44100;
		my_delay.size = 100;
		
		Jamoma::SampleBundle out_samples1 = my_delay( impulse() );
		Jamoma::SampleBundle out_samples2 = my_delay( zero );
		Jamoma::SampleBundle out_samples3 = my_delay( zero );
		
		int badSampleCount = 0;
		
		// first 64 samples should all be zero
		for (auto& channel : out_samples1) {
			for (auto& sample : channel) {
				if (sample != 0.0) {
					badSampleCount++;
					std::cout << "bad sample " << " is " << sample << std::endl;
				}
			}
		}
		
		// 100 samples later should be 1.0
		// note: this is not the 100th sample, but 100 samples after sample 0 -- a delay of 0 is sample 0
		for (auto& channel : out_samples2) {
			int i = 0;
			for (auto& sample : channel) {
				if (i == 100-64) {
					if (sample != 1.0) {
						badSampleCount++;
						std::cout << "sample " << i << " is " << sample << std::endl;
					}
				}
				else if (sample != 0.0) {
					badSampleCount++;
					std::cout << "sample " << i << " is " << sample << std::endl;
				}
				++i;
			}
		}
		
		// last 64 samples should all be zero
		for (auto& channel : out_samples3) {
			for (auto& sample : channel) {
				if (sample != 0.0) {
					badSampleCount++;
					std::cout << "bad sample " << " is " << sample << std::endl;
				}
			}
		}

		std::cout << "the output has " << badSampleCount << " bad samples" << std::endl;
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
	}

	
	/*
		Vector Size = 4
		Delay Size = 6
		Thus Buffer Size = 10
	 
		Write:	[1][0][0][0][ ][ ][ ][ ][ ][ ]
		Read:	[ ][ ][ ][ ][x][x][x][x][ ][ ]
	 
		Write:	[ ][ ][ ][ ][0][0][0][0][ ][ ]
		Read:	[x][x][ ][ ][ ][ ][ ][ ][x][x]
		
		Write:	[0][0][ ][ ][ ][ ][ ][ ][0][0]
		Read:	[ ][ ][x][x][x][x][ ][ ][ ][ ]
	 */
	void testDelayGreaterThanOneVectorSize2()
	{
		Jamoma::SampleBundle zero(1, 4);
		
		Jamoma::UnitImpulse impulse;
		impulse.channelCount = 1;
		impulse.frameCount = 4;
		
		Jamoma::Delay my_delay;
		my_delay.sampleRate = 96000;
		my_delay.size = 6;
		
		Jamoma::SampleBundle out1 = my_delay( impulse() );
		Jamoma::SampleBundle out2 = my_delay( zero );
		Jamoma::SampleBundle out3 = my_delay( zero );
		
		mTest->TEST_ASSERT("First Vector Output Correct",  out1[0][0] == 0.0 && out1[0][1] == 0.0 && out1[0][2] == 0.0 && out1[0][3] == 0.0);
		mTest->TEST_ASSERT("Second Vector Output Correct", out2[0][0] == 0.0 && out2[0][1] == 0.0 && out2[0][2] == 1.0 && out2[0][3] == 0.0);
		mTest->TEST_ASSERT("Third Vector Output Correct",  out3[0][0] == 0.0 && out3[0][1] == 0.0 && out3[0][2] == 0.0 && out3[0][3] == 0.0);
	}
	
	
	
	
	/*
		Vector Size = 4
		Delay Size = 3
		Thus Buffer Size = 7
	 
		Write:	[1][0][0][0][ ][ ][ ]
		Read:	[x][ ][ ][ ][x][x][x]
	 
		Write:	[0][ ][ ][ ][0][0][0]
		Read:	[ ][x][x][x][x][ ][ ]
		
		Write:	[ ][0][0][0][0][ ][ ]
		Read:	[x][x][ ][ ][ ][x][x]
	 */
	void testDelayLessThanOneVectorSize()
	{
		Jamoma::SampleBundle zero(1, 4);
		
		Jamoma::UnitImpulse impulse;
		impulse.channelCount = 1;
		impulse.frameCount = 4;
		
		Jamoma::Delay my_delay;
		my_delay.sampleRate = 96000;
		my_delay.size = 3;
		
		Jamoma::SampleBundle out1 = my_delay( impulse() );
		Jamoma::SampleBundle out2 = my_delay( zero );
		Jamoma::SampleBundle out3 = my_delay( zero );
		
		mTest->TEST_ASSERT("First Vector Output Correct",  out1[0][0] == 0.0 && out1[0][1] == 0.0 && out1[0][2] == 0.0 && out1[0][3] == 1.0);
		mTest->TEST_ASSERT("Second Vector Output Correct", out2[0][0] == 0.0 && out2[0][1] == 0.0 && out2[0][2] == 0.0 && out2[0][3] == 0.0);
		mTest->TEST_ASSERT("Third Vector Output Correct",  out3[0][0] == 0.0 && out3[0][1] == 0.0 && out3[0][2] == 0.0 && out3[0][3] == 0.0);
	}
	
	
	
	void testDelaySingleSample()
	{
		Jamoma::SampleVector	input = {0,1,0,0,   0,0,0,0,   2,0,0,0,   0,0,3,0 };
		Jamoma::SampleVector	output;
		Jamoma::Delay			delay;
		
		delay.size = 3;
		
		for (auto& in : input) {
			Jamoma::Sample out = delay(in);
			output.push_back(out);
		}
		
		mTest->TEST_ASSERT("First Vector Output Correct",     output[0] == 0 && output[1] == 0 && output[2] == 0 && output[3] == 0
														   && output[4] == 1 && output[5] == 0 && output[6] == 0 && output[7] == 0
														   && output[8] == 0 && output[9] == 0 && output[10] == 0 && output[11] == 2
														   && output[12] == 0 && output[13] == 0 && output[14] == 0 && output[15] == 0
						   );

	}
	
};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<DelayTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
