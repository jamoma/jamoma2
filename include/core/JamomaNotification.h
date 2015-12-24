/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Define a notification from a Jamoma::Object
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once

#include "JamomaObject.h"

namespace Jamoma {
	
	
	/** Define a notification that can be delivered by a Jamoma::Object.
	 */
	class Notification {
	public:
		
		/** Define a Notification.
			@param	name		The name of the Message when called on your Object dynamically.
			@param	synopsis	A description of what the Message does.
			@param	fn			The actual function to perform. May be a function pointer, functor, or lamba.
		 */
		Notification(String name, Synopsis synopsis, Function fn)
		: mFunction(fn)
		, mSynopsis(synopsis)
		{}
		
		
		/** Execute the Message directly as a method of the C++ class. */
		Error operator ()() {
			mFunction();
			return Error::none;	// TODO: what's the point of returning an error code in this case?
		}
		
		const Synopsis& synopsis() {
			return mSynopsis;
		}

	private:
		Function		mFunction;
		Synopsis		mSynopsis;
	};
	

	
	
	
	class Observer {
	public:
		
		// TODO: Do we really need this variation of the constructor?  YAGNI!
		//		Notification(String name, Function fn)
		//		: mFunction(fn)
		//		{}
		
		
		/** Define a Notification.
			@param	name		The name of the Message when called on your Object dynamically.
			@param	synopsis	A description of what the Message does.
			@param	fn			The actual function to perform. May be a function pointer, functor, or lamba.
		 */
		Observer(Function fn)
		: mFunction(fn)
		{}
		
		
		/** Execute the Message directly as a method of the C++ class. */
		Error operator ()() {
			mFunction();
			return Error::none;	// TODO: what's the point of returning an error code in this case?
		}
		
	private:
		Function		mFunction;
//		Synopsis		mSynopsis;
	};

	
	
	
	
} // namespace Jamoma
