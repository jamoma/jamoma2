/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Core infrastructure
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
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
