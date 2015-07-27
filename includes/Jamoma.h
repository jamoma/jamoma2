/** @file
 *
 * @ingroup jamoma2
 *
 * @brief #Jamoma.h is the starting point for the jamoma2 library.
 *
 * @details #Jamoma.h can be used to include the entire jamoma2 library in a coding project. 
 * Using the follow syntax will enable your code to find relevant functions with jamoma2: <CODE>#include "jamoma.h"</CODE>
 *
 * @author Timothy Place, Nathan Wolek
 *
 * @copyright Copyright © 2015 by Jamoma authors and contributors @n
 * This code is licensed under the terms of the "BSD 3-Clause License" @n
 * https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>


namespace Jamoma {

using String = std::string;
using Function = std::function<void(void)>;
using Text = char[];
using Classname = Text;
//using Tags = std::array<Text, 10>; // probably make this a vector of symbols instead

enum class Error {
	none,
	generic
};

	
	
	
	
constexpr double kPi	= 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068;
constexpr double kTwoPi	= kPi * 2.0;





template <typename T>
T Limit(T input, T low, T high)
{
	return std::min(std::max(input, low), high);
}


}  // namespace Jamoma


#include "JamomaSymbol.h"


#include "readerwriterqueue.h"

#include "JamomaValue.h"
#include "JamomaObject.h"
#include "JamomaAudioObject.h"
#include "JamomaSample.h"

#include "JamomaCircularStorage.h"

#include "JamomaDcblock.h"
#include "JamomaGain.h"
#include "JamomaLowpassFourPole.h"
#include "JamomaNoise.h"
#include "JamomaOverdrive.h"
