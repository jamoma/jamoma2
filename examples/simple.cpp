/** @file

	@ingroup jamoma2

	@brief Compiles an example program to test the jamoma2 library.

	@details

	@author Timothy Place, Nathan Wolek

	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#include "Jamoma.h"
#include "portaudio.h"


void CircularStorageTest()
{
	Jamoma::CircularStorage<Jamoma::Sample>		circ(8);	// 8 samples
	Jamoma::SampleVector						samples = {1,2,3,4,5};
	
	// write tests
	circ.write(samples);
	
	samples = {6,7,8,9,10};
	circ.write(samples);

	// read tests
	
	Jamoma::SampleVector	foo(3);
	circ.read(foo);
	circ.read(foo);
	
	samples = {20, 21, 22};
	circ.write(samples);
	circ.read(foo);
	
	samples = {100, 101, 102};
	circ.write(samples);
	circ.read(foo);
	
	foo.resize(5);
	circ.read(foo);
}


void SampleBundleAndGainTest()
{
	// gain -- single sample
	
	Jamoma::Gain	my_gain;
	Jamoma::Sample	x = 1.0;
	Jamoma::Sample	y = 0.0;
	
	my_gain.gain = 0.5;
	y = my_gain(x);
	
	// gain -- vector
	
	Jamoma::SampleBundle	in_samples(2, 8);
	
	in_samples.fill(1.0);
	auto out_samples = my_gain(in_samples);
	
	my_gain.gain = 0.25;
	in_samples = out_samples;
	out_samples = my_gain(in_samples);
	
	// samplebundle
	
	auto bar = in_samples[0][0];
	std::cout << "the sample is " << bar << std::endl;
	
	in_samples[0][0] = 2.0;
	auto foo = in_samples[0][0];
	std::cout << "the sample is " << foo << std::endl;
}

void LowpassFourPoleTest()
{
    Jamoma::LowpassFourPole my_lowpass;
    
    my_lowpass.sampleRate = 44100;
    my_lowpass.frequency = 1000.;
    my_lowpass.q = 1.0;
    
    Jamoma::SampleBundle impulse(1, 64);
    impulse[0][0] = 1.0;
    
    Jamoma::SampleVector expectedImpulse = {
        1.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0, 
        0.0
    };
    
    int badSampleCount = 0;
    
    for (int i = 0; i < expectedImpulse.size(); i++)
    {
        if (expectedImpulse[i] != impulse[0][i]) badSampleCount++;
    }
    
    std::cout << "the impulse signal has " << badSampleCount << " bad samples" << std::endl;
    
    auto out_samples = my_lowpass(impulse);
    
    // the following impulse was created using the code here
    // http://musicdsp.org/archive.php?classid=3#26
    // within Processing
    // cutoff = 1000
    // q = 1.0
    Jamoma::SampleVector expectedIR = {
        2.681802833344647E-6,
        1.3381033668168877E-5,
        3.7714134294038155E-5,
        8.027046605044782E-5,
        1.4446236531090402E-4,
        2.3266652549250506E-4,
        3.4637395387999775E-4,
        4.863232608379854E-4,
        6.52618864392983E-4,
        8.448355631598002E-4,
        0.001062110809309293,
        0.001303225900357731,
        0.0015666772036194987,
        0.0018507384298140377,
        0.0021535148821610743,
        0.002472990523942391,
        0.0028070686305651303,
        0.0031536067212494284,
        0.0035104464002100612,
        0.0038754386772468273,
        0.00424646528265345,
        0.004621456440965131,
        0.004998405521970396,
        0.0053753809453081,
        0.005750535676565311,
        0.006122114617811144,
        0.006488460163685845,
        0.006848016165268556,
        0.00719933051774118,
        0.007541056564133758,
        0.007871953485976737,
        0.008190885832308944,
        0.00849682232102107,
        0.0087888340307896,
        0.0090660920877235,
        0.009327864938164877,
        0.009573515287725065,
        0.009802496776478823,
        0.010014350451170672,
        0.010208701087206644,
        0.010385253406017963,
        0.010543788227004214,
        0.010684158587613332,
        0.010806285860121976,
        0.010910155889276336,
        0.010995815171080003,
        0.011063367089617093,
        0.011112968225825411,
        0.011144824749540717, 
        0.01115918890387774, 
        0.011156355589059313, 
        0.01113665905111804, 
        0.011100469679444743, 
        0.01104819091591722, 
        0.01098025627728667, 
        0.010897126491605477, 
        0.010799286748728779, 
        0.010687244064295689, 
        0.010561524756078145, 
        0.010422672031161895, 
        0.010271243682082553, 
        0.010107809889768535, 
        0.0099329511309322, 
        0.009747256187391761
    };
    
    badSampleCount = 0;
    Jamoma::Sample temp = 0.0;
    Jamoma::Sample tempExpected = 0.0;

    for (int i = 0; i < expectedIR.size(); i++)
    {
        temp = out_samples[0][0][i];
        tempExpected = expectedIR[i];
        if (temp != tempExpected) {
            badSampleCount++;
            std::cout << "sample " << i << " expected " << expectedIR[i] << " but instead was " << temp << std::endl;
        }
    }
    
    std::cout << "the impulse response of my_lowpass has " << badSampleCount << " bad samples" << std::endl;
    
}


class MyGraph {
public:
	Jamoma::WhiteNoise				random;
	Jamoma::WhiteNoise				noise;
	Jamoma::Dcblock					dcblock;
	Jamoma::LowpassFourPole			lowpass;
	Jamoma::SharedSampleBundleGroup	output;

	
	MyGraph()
	{
		noise.channelCount = 2;		// these should be set a queriable properties of the graph
		noise.frameCount = 2048;	// ... so that multiple sources can simply ask the graph for this information
		
		lowpass.sampleRate = 44100;
		lowpass.frequency = 1000.0;
		lowpass.q = 38.0;
	}

	
	void process(float*	out,  unsigned long framesPerBuffer)
	{
		output = lowpass( dcblock( noise() ) );		// our "graph"
		
		for (int i=0; i<framesPerBuffer; i++ ) {
			*out++ = output[0][0][i];
			*out++ = output[0][1][i];
		}
	}
	
};


// next test -- use std::chrono to sequence a filter cf on noise input and then quit?

static int PortAudioExampleCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData)
{
	MyGraph* graph = (MyGraph*)userData;
	
	graph->process((float*)outputBuffer, framesPerBuffer);
	return 0; // we aren't done -- we want to run forever
}


void PortAudioExample()
{
	MyGraph				graph;
	PaStream*           stream;
	PaError             err;
	PaStreamParameters  outputParameters;
	static const double SR  = 44100.0;
	static const int    FPB = 2048; // Frames per buffer
	
	err = Pa_Initialize();
	if (err != paNoError)
		goto error;
	
	// Open a stereo PortAudio stream so we can hear the result.
	outputParameters.device = Pa_GetDefaultOutputDevice(); // Take the default output device.
	if (outputParameters.device == paNoDevice) {
		fprintf(stderr,"Error: No default output device.\n");
		goto error;
	}
	outputParameters.channelCount = 2;
	outputParameters.hostApiSpecificStreamInfo = NULL;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	
	err = Pa_OpenStream(&stream,
						NULL,                              // No input.
						&outputParameters,
						SR,                                // Sample rate.
						FPB,                               // Frames per buffer.
						paClipOff, // we won't output out of range samples so don't bother clipping them
						PortAudioExampleCallback,
						(void*)&graph);
	
	if (err != paNoError)
		goto error;
	
	err = Pa_StartStream( stream );
	if (err != paNoError)
		goto error;
	
	// Loop until the callback returns non-zero
	while ( ( err = Pa_IsStreamActive( stream ) ) == 1 )
		Pa_Sleep(100);
	
	if (!err)
		err = Pa_CloseStream(stream);
error:
	Pa_Terminate();
}


int main(int argc, const char * argv[])
{
	std::cout << "Hello, World!\n";

	CircularStorageTest();
	SampleBundleAndGainTest();
    LowpassFourPoleTest();
	PortAudioExample();

	return 0;
}
