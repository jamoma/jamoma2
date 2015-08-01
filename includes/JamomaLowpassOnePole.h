/** @file
	
	@ingroup jamoma2
	
	@brief Apply a first-order low-pass filter to samples.
	
	@author Nathan Wolek
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"

namespace Jamoma {
    
    /**	This AudioObject applies a basic <a href="https://en.wikipedia.org/wiki/Low-pass_filter">low-pass filter</a> to a Sample or SampleBundle.
     */
    class LowpassOnePole : public AudioObject {
        
    };
    
    
}  // namespace Jamoma