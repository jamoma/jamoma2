//
//  JamomaObject.h
//  JamomaExperiments
//
//  Created by Timothy Place on 3/27/15.
//  Copyright (c) 2015 jamoma. All rights reserved.
//

#pragma once

#include <cassert>
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
