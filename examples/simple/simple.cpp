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
		lowpass.resonance = 38.0;
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

	SampleBundleAndGainTest();
	PortAudioExample();

	return 0;
}
