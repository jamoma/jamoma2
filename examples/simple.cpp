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
    
    // the following impulse was w Jamoma Ruby implementation
    // cutoff = 1000
    // q = 1.0
    Jamoma::SampleVector expectedIR = {
        0.00026123201253651704,
        0.0011857023260037412,
        0.00300786893686996,
        0.0057218719398896885,
        0.009163570088690492,
        0.013096920656460918,
        0.017270696501776345,
        0.02145175608559647,
        0.025442510213163474,
        0.02908804721685234,
        0.03227676574307599,
        0.03493718263289108,
        0.03703272568508792,
        0.03855570535614742,
        0.039521223124312325,
        0.039961469874449096,
        0.03992065947235377,
        0.03945070389439048,
        0.03860764692732276,
        0.03744881883918096,
        0.036030643775092054,
        0.03440701714557044,
        0.03262816635337268,
        0.030739910891117425,
        0.028783244381474997,
        0.026794169647219417,
        0.024803727143714854,
        0.02283816626493955,
        0.020919217664754,
        0.01906443255383986,
        0.017287561821773555,
        0.015598953770523711,
        0.01400595426705292,
        0.012513297299751567,
        0.011123477344509214,
        0.009837097705712837,
        0.008653191188523784,
        0.007569511169055432,
        0.006582792438263008,
        0.005688982174211909,
        0.004883442107504695,
        0.0041611234388107595,
        0.0035167163903050817,
        0.002944776461706314,
        0.002439829547377854,
        0.0019964580788928024,
        0.0016093703080559978,
        0.0012734547550720236,
        0.000983821728412055,
        0.0007358336872232467,
        0.0005251260717924123, 
        0.0003476200786875908, 
        0.0001995287092981665, 
        7.735727689265714e-05, 
        -2.2100579646692944e-05, 
        -0.00010177045600200423, 
        -0.0001643075166693624, 
        -0.00021210891332541597, 
        -0.00024732769741041695, 
        -0.0002718877273622131, 
        -0.00028749915185794064, 
        -0.00029567412237107036, 
        -0.0002977424518631175, 
        -0.000294866992089446, 
        -0.0002880585504234669
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
