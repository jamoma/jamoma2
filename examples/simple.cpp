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

void LowpassFourPoleTest()
{
    Jamoma::LowpassFourPole my_lowpass;
    
    my_lowpass.sampleRate = 44100;
    my_lowpass.frequency = 1000.;
    my_lowpass.resonance = 10.0;
    
    Jamoma::UnitImpulse impulse;
    
    impulse.channelCount = 1;
    impulse.frameCount = 64;
    
    auto out_samples = my_lowpass( impulse() );
    
    // The following impulse was based on the code found here
    // http://musicdsp.org/archive.php?classid=3#26
    // implemented in Processing by NW, adopting tweaks made in jamoma2.
    // It should correspond to the following settings:
    // cutoff = 1000
    // q = 10.0
    Jamoma::SampleVector expectedIR = {
        1.1114094966912524E-4,
        5.185809867004247E-4,
        0.0013566830733495131,
        0.00266711884609515,
        0.004419756543933562,
        0.006540995119517765,
        0.008934880451193566,
        0.011497619575988889,
        0.014127212462044219,
        0.016729524194462317,
        0.01922180477418673,
        0.021534415062963778,
        0.02361132349572916,
        0.025409788493738057,
        0.026899527152547734,
        0.028061584347418934,
        0.028887051817754188,
        0.02937573913186519,
        0.029534863739063902,
        0.029377802449531133,
        0.02892292917914669,
        0.02819255174120884,
        0.0272119523870212,
        0.026008531572689723,
        0.0246110512183134,
        0.023048971903299378,
        0.021351877550629245,
        0.019548980864406137,
        0.01766870286642576,
        0.015738320168397234,
        0.013783674009326336,
        0.01182893551333184,
        0.009896422039881662,
        0.008006459883080358,
        0.006177288918901074,
        0.004425005097042377,
        0.002763536930312534,
        0.0012046523547523686,
        -2.4200747504493246E-4,
        -0.0015688707217329722,
        -0.002770356844647906,
        -0.003842780991240676,
        -0.004784243629542635,
        -0.005594508112436378,
        -0.006274868724514015,
        -0.006828011618719647,
        -0.00725787090172078,
        -0.007569481973642979,
        -0.0077688340695979425,
        -0.007862723787941745, 
        -0.007858611224353948, 
        -0.007764480162803003, 
        -0.007588703605585956, 
        -0.007339915756309998, 
        -0.007026891403352279, 
        -0.006658433488399313, 
        -0.0062432694864702305, 
        -0.00578995707161646, 
        -0.005306799397393739, 
        -0.004801770184216497, 
        -0.0042824486776811615, 
        -0.0037559644235848214, 
        -0.0032289516972181694, 
        -0.0027075133269751014
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
    
    std::cout << "the impulse response of my_lowpass (4 pole) has " << badSampleCount << " bad samples" << std::endl;
	
	assert(badSampleCount == 0);
	
	// Test range limiting
	my_lowpass.frequency = 100.0;
	assert(my_lowpass.frequency == 100.0);

	my_lowpass.frequency = 5.0;
	assert(my_lowpass.frequency == 20.0);
	
	// TODO: boundaries for this object need to change when the sampleRate changes -- currently they don't!
	// So we do this test with the initial sampleRate instead of with `my_lowpass.sampleRate`
	my_lowpass.frequency = 100000;
	assert(my_lowpass.frequency < 96000 * 0.5);
	
	// q is not clipped at the moment, so we can do irrational bad things...  we should change this
	my_lowpass.resonance = 100.0;
	assert(my_lowpass.resonance == 100.0);
	
	my_lowpass.resonance = -5.0;
	assert(my_lowpass.resonance == -5.0);
	
	
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

	CircularStorageTest();
	SampleBundleAndGainTest();
    UnitImpulseTest();
    LowpassOnePoleTest();
    LowpassFourPoleTest();
	PortAudioExample();

	return 0;
}
