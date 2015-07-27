//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

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
