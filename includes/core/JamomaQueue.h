/** @file
	
	@ingroup jamoma2
	
	@brief Core infrastructure
 
	@author Timothy Place
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include "JamomaEvent.h"


namespace Jamoma {
	
	
	using Queue = ReaderWriterQueue<Event>;
	using QueuePool = std::unordered_map<std::thread::id, Queue>;
	
	// TODO: global QueuePool
	// TODO: what about temp per-object queues -- can we fabricate ids?
	

} // namespace Jamoma
