/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Core infrastructure
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#pragma once

#include "JamomaEvent.h"


namespace Jamoma {
	
	
	using Queue = ReaderWriterQueue<Event>;
	using QueuePool = std::unordered_map<std::thread::id, Queue>;
	
	// TODO: global QueuePool
	// TODO: what about temp per-object queues -- can we fabricate ids?
	

} // namespace Jamoma
