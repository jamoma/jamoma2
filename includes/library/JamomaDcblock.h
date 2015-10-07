/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Block DC offset within samples.
		
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {

	
	/**	This AudioObject removes DC offset (sometimes called <a href="https://en.wikipedia.org/wiki/DC_bias">DC bias</a> from a Sample or SampleBundle.
		The process is acheived by applying a first-order highpass filter to the input.
	 
		This first-order highpass filter algorithm is used pretty much everywhere (STK, ChucK, RTCMix, SuperCollider, Max, Pd, etc),
		with the difference equation:

			y(n) = (1 * x(n))  +  (-1 * x(n-1))  -  (-0.9997 * y(n-1))  ,  n = 0, 1, 2, 3, ...

		which can be simplified to:

			y(n) = x(n) - x(n-1) + (0.9997 * y(n-1))

		and thus characterized by the Z-transform:

			Y(z) = X(z)  -  X(z) * z^(-1)  +  Y(z) * 0.9997 * z^(-1)

		meaning the transfer function is:

			H(z) = [1  -  z^(-1)]  /  [1  +  0.9997 * z^(-1)]

		and resulting in the frequency response:

			H( e^(i*omega*T) ) = [1  -  e^(-i * omega * T)]  /  [1  +  0.9997 * e^(-i * omega * T)]

		where $i$ is the sqrt(-1), e is Euler's log base, T is the sampling interval, and omega is 2*pi*frequency.

		In Max, it usually shows up simply as [biquad~ 1.0 -1.0 0.0 -0.9997 0.0].
		In other places it usually shows up with the feedback coefficient set to -0.995
		(e.g in SuperCollider and in [JOS, 2007, pp 273]).
		The higher coefficient is desirable so as to not attenuate lowish frequencies in the spectrum,
		but with the caveat that it also won't respond as quickly to varying amounts DC Offset.

		The power is attenuated by -3 dB at a normalized frequency of 0.1612 * pi @ 0.9997.
		At fs=44100 this translates to cf = 22050 * 0.1612 = 3554.46 Hz.

		The power is attenuated by -3 dB at a normalized frequency of 0.1604 * pi @ 0.995.
		At fs=44100 this translates to cf = 22050 * 0.1604 = 3536.82 Hz.

		For reference, in this last case, the power is attenuated by -6 db (magnitude attenuated by -12 dB) @ 0.0798 * pi,
		which at fs=44100 translates to 1759.59 Hz.

		----

		So what are benefits of this filter?  In the case of biquad~ in Max, we are processing with 2 coefficients zeroed,
		meaning that we burn the cpu for a second-order filter when we are only getting the benefit of a first-order filter.
		Why would we want to do this instead of doing something like a using a Butterworth filter for DC Blocking?

		We could implement a nice third-order Butterworth with a cf=20 Hz @ fs=48000 that would not disturb the gain of the spectrum,
		but...  the filter does not have linear phase.

		Since we are outside of Max, we can evaluate this filter for what it is: a first-order filter.
		The clear benefit then is its speed.
		- however, if we used a pure FIR filter then we could potentially use SSE instructions, so:
		how would a second-order FIR compare to this classical first-order FIR/IIR combination?
	 */
	class Dcblock : public AudioObject {
		
		AdaptingSampleBundle	mX = { this };	///< Input history -- AdaptingSampleBundle type will update channelCount automagically as needed
		AdaptingSampleBundle	mY = { this };	///< Output history -- AdaptingSampleBundle type will update channelCount automagically as needed
		
	public:
		static constexpr Classname classname = { "dcblock" };
		static constexpr auto tags = { "dspFilterLib", "audio", "filter" };
		
		
		/**	Resets the DC-Blocking filter.
			This algorithm uses an IIR filter, meaning that it relies on feedback.  
			If the filter should not be producing any signal (such as turning audio off and then back on in a host) 
			or if the feedback has become corrupted (such as might happen if a NaN is fed in) 
			then it may be neccesary to clear the filter by calling this method.
		 */
		Message			clear = { "clear", [this]{
									mX.fill(0.0);
									mY.fill(0.0);
								}
		};
		
		
		/** Process one sample.
			@param x					Sample to be processed.
			@return					Processed sample.
		 */
		Sample operator()(Sample x)
		{
			return (*this)(x, 0);
		}
		
		
		/** Process one sample at a specified channel.
			@param x					Sample to be processed.
			@param channel				The channel.
			@return					Processed sample.
		 */
		Sample operator()(Sample x, int channel)
		{
			Sample y = x - mX[channel][0] + (mY[channel][0] * 0.9997);
			
			ZeroDenormal(y);
			mY[channel][0] = y;
			mX[channel][0] = x;
			return y;
		}
		
		
		/** Process a SharedSampleBundleGroup.
			@param	x	SharedSampleBundleGroup to be processed.
			@return		Processed SharedSampleBundleGroup.
		 */
		SharedSampleBundleGroup operator()(const SampleBundle& x)
		{
			auto out = adapt(x);
			
			for (int channel=0; channel < x.channelCount(); ++channel) {
				for	(int i=0; i < x.frameCount(); ++i)
					out[0][channel][i] = (*this)(x[channel][i], channel);
			}
			return out;
		}

	};

} // namespace Jamoma
