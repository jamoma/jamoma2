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
    int quarterSampleRate = my_lowpass.sampleRate / 4;
    std::cout << "the sampleRate of my_lowpass is " << quarterSampleRate << std::endl;
    
    my_lowpass.frequency = quarterSampleRate;
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
    
    // the following impulse is based on
    // cutoff = fourth the sample rate
    // q = 1.0
    Jamoma::SampleVector expectedIR = {
        0.0396224419529398,
        0.11262191851792265,
        0.16263850742922237,
        0.1580464966677373,
        0.11010722879084384,
        0.04734558258529685,
        -0.005878827664754886,
        -0.037119534077695325,
        -0.04532940124415245,
        -0.03680673495851141,
        -0.0204812942585793,
        -0.004224875152348398,
        0.0071092938759238795,
        0.011993611126351418,
        0.011418123337395742,
        0.007634631453980186,
        0.003000341947083423,
        -7.697849883977733E-4,
        -0.002873215656351384,
        -0.0033132755809141975,
        -0.0025912841816780807,
        -0.0013664503105725913,
        -1.9788740064962963E-4,
        5.850884319961658E-4,
        8.942968534084026E-4,
        8.173373111971232E-4,
        5.243600224643831E-4,
        1.8556051471780037E-4,
        -7.992176614478644E-5,
        -2.2032122482124926E-4,
        -2.4112791897038855E-4,
        -1.816370531597656E-4,
        -9.028170345582544E-5,
        -6.615987887816611E-6,
        4.7176027665434814E-5,
        6.632444123882351E-5,
        5.827397277540053E-5,
        3.579816655176653E-5,
        1.1136225875440025E-5,
        -7.4771058514166505E-6,
        -1.6758322624231378E-5,
        -1.7475292721626308E-5,
        -1.2674040161348515E-5,
        -5.89697114444503E-6,
        6.939799242323658E-8,
        3.7429737571232865E-6,
        4.894217724391685E-6,
        4.138075710286668E-6,
        2.427826580827559E-6, 
        6.401203412850543E-7, 
        -6.589682200514544E-7, 
        -1.2655812224739843E-6, 
        -1.261335186083446E-6, 
        -8.801166302161978E-7, 
        -3.798974471261685E-7, 
        4.386687616163528E-8, 
        2.9309723033879503E-7, 
        3.5944886136244874E-7, 
        2.9264565139479614E-7, 
        1.6344326324112478E-7, 
        3.438305167079229E-8, 
        -5.5851738514901825E-8, 
        -9.496168796636556E-8, 
        -9.067604089159774E-8
    };
    
    badSampleCount = 0;
    Jamoma::Sample temp = 0.0;

    for (int i = 0; i < expectedIR.size(); i++)
    {
        temp = out_samples[0][0][i];
        if (expectedIR[i] != temp) badSampleCount++;
        // std::cout << temp - expectedIR[i]  << std::endl; // look at difference
    }
    
    std::cout << "the impulse response of my_lowpass has " << badSampleCount << " bad samples" << std::endl;
    
}


class MyGraph {
public:
	Jamoma::Noise					random;
	Jamoma::Noise					noise;
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
