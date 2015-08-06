/** @file
	
	@ingroup jamoma2
	
	@brief Core infrastructure
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaObject.h"

namespace Jamoma {
	
	
	/** An Event in Jamoma may be one of three types:
		- Message
		- Parameter
		- Notification
	 
		Events represent actions taken on an object that may or may not be queued to occur asynchronously.
	 */
	class Event {
	public:
		

		
	private:
		Function		mFunction;
		Synopsis		mSynopsis;
		
	};
	

} // namespace Jamoma
