/** @file
	
	@ingroup jamoma2
	
	@brief Generate one sample at maximum amplitude for testing.
	
	@author Nathan Wolek
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaAudioObject.h"


namespace Jamoma {
    
    /** This AudioObject generates a unit impulse function (sometimes called  <a href="https://en.wikipedia.org/wiki/Dirac_delta_function">Dirac function</a> by setting the initial Sample to one and filling the remainder of the SampleBundle with zeros.
        This function is typically used to test the <a href="https://en.wikipedia.org/wiki/Impulse_response">impulse response</a> of a time-invariant filter.
     */
    class UnitImpulse : public AudioObject {
        
    };
    

} // namespace Jamoma