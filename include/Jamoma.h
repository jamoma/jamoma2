/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Jamoma.h is the starting point for the jamoma2 library.
	
	@details 	Jamoma.h can be used to include the entire jamoma2 library in a coding project. 
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>


namespace Jamoma {

	using String = std::string;
	using Text = char[];
	using Classname = Text;
	//using Tags = std::array<Text, 10>; // probably make this a vector of symbols instead
	using TimePoint = std::chrono::high_resolution_clock::time_point;

		
	/**	A brief string documenting a Function/Parameter/Message/Notification/Class/Etc.	*/
	using Synopsis = String;


	enum class Error {
		none,
		generic
	};

	
	/**	Tag a value with some sort of marker such as a unit of measure, a label, etc.
		@param	a		The value
		@param	tag		The tag
		@return			A pair containing both the value and the tag.
	 */
	template<typename T, typename U>
	auto Tag(T a, U tag) {
		return std::make_pair(a, tag);
	}
	
		
		
	constexpr double kPi				= 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068; ///z The mathematical constant PI = 3.14...
	constexpr double kTwoPi				= kPi * 2.0;			///< Two times the constant PI (2 * kPi)
	constexpr double kDegToRad			= kPi / 180.0;			///< Coefficient for converting degrees to radians
	constexpr double kRadToDeg			= 180.0 / kPi;			///< Coefficient for converting radians to degrees
	
	/** A constant used when converting between midi and linear gain.
	 @details:	This conversion is set up such that:
				  0 midigain equals -96 dB, and both gets mapped to linear 0
				100 midigain equals   0 dB
				127 midigain equals +12 dB
	 */
	const double kGainMidiPower		= log((log(12./96. + 1.))/(log(127./100.)))/log(2.);
	const double kGainMidiPowerInv	= 1.0/kGainMidiPower;		///< The inverse of #kGainMidiPower
	const double kGainMidiPowPow2	= pow(2, kGainMidiPower);	///< Two to the power of #kGainMidiPower
	
	
	/** Filter out denormaled values, which can make processing extremely slow when present.
		Calculation is performed in-place.
		Calculation is only performed if JAMOMA_SQUASH_DENORMALS is defined as a preprocessor symbol.
		
		We do this so that we can easily change the behavior of the routines for squashing denormals.
		* On the PPC we don't want to waste cycles unneccessarily;
		* On the Intel processors we can use SSE intrinsics as suggested by Nils Peters (see redmine ticket #799)
		* or we can use SSE intrinsics to disable denormals on a processor completely, in which case these functions should not waste cycles doing anything;
		* On ARM processors what happens?  We might still need to squash denormals, or maybe there is an option as indicated @ http://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html

		Implementation Note:  The __SSE3__ symbol is always defined in Xcode despite any changes you make to compiler settings
		On Linux, the __SSE3__ symbol is toggled based on passing the -msse3 flag to GCC
		On Windows, the __SSE3__ symbol is always UNdefined, despite any changes you make to compiler settings
		So this symbol is completely useless.
	 
		When SSE3 is available, then we rely on the denormals being turned-off using a bit in the processor's control register
		http://software.intel.com/sites/products/documentation/studio/composer/en-us/2011/compiler_c/fpops/common/fpops_set_ftz_daz.htm
	 
		For example, anything running the Max environment will be setting this bit on every thread and so we don't need to do anything at all.
	 */
	template<class T>
	static void ZeroDenormal(T& value)
	{
#ifdef JAMOMA_SQUASH_DENORMALS
		if (!std::isnormal(value))
			value = 0;
#endif
	}



}  // namespace Jamoma



// Dependencies

//#include "readerwriterqueue.h"


#include "third-party/murmur/Murmur3.h" // used for constexpr hash function

/** A hash function using the Murmur3 algorithm ( https://en.wikipedia.org/wiki/MurmurHash ).
 This hash function is capable of being executed at compile time,
 meaning that the compiled binary will have a constant int value and no actually need to execute any code at runtime.
 @param	str		A c-string to be hashed into an int.
 @param	seed	An optional seed value.  For most uses you should not override the default.
 @return			An int (specifically a uint32_t) representing the hash of the string input.
 */
constexpr inline uint32_t Hash(const char *const str, const uint32_t seed = 0xAED123FD) noexcept
{
	return Murmur3_32(str, _StringLength(str), seed);
}


// Core

#include "JamomaGenerator.h"
#include "JamomaLimit.h"
#include "JamomaDataspace.h"
#include "JamomaInterpolator.h"
#include "JamomaVar.h"
#include "JamomaFunction.h"

#include "JamomaObject.h"
#include "JamomaMessage.h"
#include "JamomaNotification.h"
#include "JamomaParameter.h"
#include "JamomaAudioObject.h"
#include "JamomaSample.h"


#include "JamomaCircularStorage.h"
#include "JamomaDelay.h"
#include "JamomaUnitTest.h"


// Units

#include "JamomaAllpass1.h"
#include "JamomaDcblock.h"
#include "JamomaDelay.h"
#include "JamomaGain.h"
#include "JamomaLimiter.h"
#include "JamomaLowpassOnePole.h"
#include "JamomaLowpassFourPole.h"
#include "JamomaSync.h"
#include "JamomaWhiteNoise.h"
#include "JamomaUnitImpulse.h"
