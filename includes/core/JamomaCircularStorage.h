/** @file
	
	@ingroup jamoma2
	
	@brief Read and write items within a circular container.
	
	@author Timothy Place, Nathan Wolek
	
	@copyright Copyright © 2015 by Jamoma authors and contributors @n
	This code is licensed under the terms of the "BSD 3-Clause License" @n
	https://github.com/jamoma/jamoma2/blob/master/LICENSE.md @n
 */

#pragma once

#include <thread>
#include <cassert>

namespace Jamoma {

	
	/**	A generic circular buffer designed specifically for access from a single thread.
	 
		Allows items of a single datatype to be written into a vector that wraps around to the beginning whenever the end is exceeded.
		Reading items from the vector can then return chunks of the N most recent items.
		The initial design of this class was for use as an audio sample delay buffer, 
		however it's functionality has been generalized to allow for other datatypes and applications.
	 */
	template <class T>
	class CircularStorage {
		friend class CircularStorageTest;
		
		std::vector<T>		mItems;										///< storage for the circular buffer's data
		std::size_t			mIndex = { 0 };								///< location of the record head
		std::thread::id		mThread = { std::this_thread::get_id() };	///< used to ensure we don't access unsafely from multiple threads
	
	public:
		/** Constructor specifies a fixed size for the container.
			If you want a different size, create a new container and dispose of the one you don't want.
		 */
		CircularStorage(std::size_t itemCount)
		: mItems(itemCount)
		{}
		
		
		virtual ~CircularStorage()
		{}
		
		
		/** Write a block of things into the container. 
			@param	newInput	A block of things to add. May not be larger than the size of the buffer.
		 */
		void write(const std::vector<T>& newInput)
		{
			assert(std::this_thread::get_id() == mThread);
			assert(newInput.size() <= mItems.size());
			
			std::size_t count = newInput.size();
			std::size_t roomRemaining = mItems.size() - mIndex;
			bool		wrap = false;
			
			if (count > roomRemaining) {
				count = roomRemaining;
				wrap = true;
			}
			
			std::copy_n(newInput.begin(), count, mItems.begin()+mIndex);
			mIndex += count;
			
			if (wrap) {
				std::size_t offset = count;

				count = newInput.size() - offset;
				std::copy_n(newInput.begin()+offset, count, mItems.begin());
				mIndex = count;
			}
		}
		
		
		/** Read a block of things out from the container.
			These will be the N most recent items added to the history.
			@param	output	A place to write the block of things from the buffer. 
							The size of this buffer will determine the number of things to request. 
							May not be larger than the size of the buffer.
		 */
		void read(std::vector<T>& output)
		{
			assert(std::this_thread::get_id() == mThread);
			assert(mItems.size() >= output.size());
			
			long	count = output.size();
			long	start = mIndex - count;
			bool	wrap = false;
			
			if (start<0) {
				count = -start;
				start = mItems.size() + start;
				wrap = true;
			}
			
			std::copy_n(mItems.begin()+start, count, output.begin());
			
			if (wrap) {
				std::size_t offset = count;
				
				count = output.size() - offset;
				std::copy_n(mItems.begin(), count, output.begin()+offset);
			}
		}
	};
	
	
} // namespace Jamoma
