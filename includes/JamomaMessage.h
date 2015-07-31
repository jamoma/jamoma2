/** @file
	
	@ingroup jamoma2
	
	@brief Define a message to a JamomaObject
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaObject.h"

namespace Jamoma {
	
	
	class Message {
	public:
		
		Message(String name, Function fn)
		: mFunction(fn)
		{}
		
		Message(String name, Synopsis synopsis, Function fn)
		: mFunction(fn)
		, mSynopsis(synopsis)
		{}
		
		Error operator ()() {
			mFunction();
			return Error::none;
		}
		
	private:
		Function		mFunction;
		Synopsis		mSynopsis;
	};
	

} // namespace Jamoma
