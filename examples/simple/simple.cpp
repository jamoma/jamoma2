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

void UnitImpulseTest()
{
    Jamoma::UnitImpulse my_impulse;
    
    my_impulse.channelCount = 1;
    my_impulse.frameCount = 64;
    
    auto output = my_impulse();
    
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
        if (expectedImpulse[i] != output[0][0][i])
        {
            badSampleCount++;
            std::cout << "sample " << i << " expected " << expectedImpulse[i] << " but instead was " << output[0][0][i] << std::endl;
        }
        
    }
    
    std::cout << "unit impulse has " << badSampleCount << " bad samples" << std::endl;
    
    assert(badSampleCount == 0);
    
}

void LowpassOnePoleTest()
{
    Jamoma::LowpassOnePole my_lowpass;
    
    my_lowpass.coefficient = 0.5;
    
    Jamoma::UnitImpulse impulse;
    
    impulse.channelCount = 1;
    impulse.frameCount = 64;
    
    auto out_samples = my_lowpass( impulse() );
    
    // The following impulse was based on the code from jamoma
    // implemented in Processing by NW
    Jamoma::SampleVector expectedIR = {
        0.5,
        0.25,
        0.125,
        0.0625,
        0.03125,
        0.015625,
        0.0078125,
        0.00390625,
        0.001953125,
        9.765625E-4,
        4.8828125E-4,
        2.44140625E-4,
        1.220703125E-4,
        6.103515625E-5,
        3.0517578125E-5,
        1.52587890625E-5,
        7.62939453125E-6,
        3.814697265625E-6,
        1.9073486328125E-6,
        9.5367431640625E-7,
        4.76837158203125E-7,
        2.384185791015625E-7,
        1.1920928955078125E-7,
        5.9604644775390625E-8,
        2.9802322387695312E-8,
        1.4901161193847656E-8,
        7.450580596923828E-9,
        3.725290298461914E-9,
        1.862645149230957E-9,
        9.313225746154785E-10,
        4.6566128730773926E-10,
        2.3283064365386963E-10,
        1.1641532182693481E-10,
        5.820766091346741E-11,
        2.9103830456733704E-11,
        1.4551915228366852E-11,
        7.275957614183426E-12,
        3.637978807091713E-12,
        1.8189894035458565E-12,
        9.094947017729282E-13,
        4.547473508864641E-13,
        2.2737367544323206E-13,
        1.1368683772161603E-13,
        5.6843418860808015E-14,
        2.8421709430404007E-14,
        1.4210854715202004E-14,
        7.105427357601002E-15,
        3.552713678800501E-15,
        1.7763568394002505E-15,
        8.881784197001252E-16, 
        4.440892098500626E-16, 
        2.220446049250313E-16, 
        1.1102230246251565E-16, 
        5.551115123125783E-17, 
        2.7755575615628914E-17, 
        1.3877787807814457E-17, 
        6.938893903907228E-18, 
        3.469446951953614E-18, 
        1.734723475976807E-18, 
        8.673617379884035E-19, 
        4.3368086899420177E-19, 
        2.1684043449710089E-19, 
        1.0842021724855044E-19, 
        5.421010862427522E-20
    };
    
    int badSampleCount = 0;
    Jamoma::Sample temp = 0.0;
    Jamoma::Sample tempExpected = 0.0;
    
    for (int i = 0; i < expectedIR.size(); i++)
    {
        temp = out_samples[0][0][i];
        tempExpected = expectedIR[i];
        if (std::fabs(temp - tempExpected) > 0.000000005) { // TODO: implement proper double comparison - issue #26
            badSampleCount++;
            std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            //" expected " << expectedIR[i] << " but instead was " << temp << std::endl;
        }
    }
    
    std::cout << "the impulse response of my_lowpass (1 pole) has " << badSampleCount << " bad samples" << std::endl;
    
    assert(badSampleCount == 0);
    
    // testing range limitations
    my_lowpass.coefficient = 0.7;
    assert(my_lowpass.coefficient == 0.7);
    
    my_lowpass.coefficient = -1.0;
    assert(my_lowpass.coefficient == 0.0);
    
    my_lowpass.coefficient = 1.2;
    assert(my_lowpass.coefficient == 1.0);
    
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
    UnitImpulseTest();
    LowpassOnePoleTest();
	PortAudioExample();

	return 0;
}
