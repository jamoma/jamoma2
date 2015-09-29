/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Various functions for limiting the range of a value.
 
	@author 	Timothy Place, Nils Peters, Tristan Matthews
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {


	template <typename T>
	T Limit(T input, T low, T high)
	{
		return std::min(std::max(input, low), high);
	}

	
	/**	Limit input to power-of-two values.
		Non-power-of-two values are increased to the next-highest power-of-two upon return.
		Only works for ints up to 32-bits.
		@seealso http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
	 */
	template<class T>
	void TTLimitPowerOfTwo(T value)
	{
		value--;
		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;
		++value;
		return value;
	}
	
	
	/**	Determine id a value is a power-of-two. Only works for ints. */
	template<class T>
	bool IsPowerOfTwo(T value)
	{
		return (value > 0) && ((value & (value-1)) == 0);
	}


	/** This routine wrapping around the range as much as necessary */
	template<class T>
	T Wrap(T input, const T low_bound, const T high_bound)
	{
		if ((input >= low_bound) && (input < high_bound))
			return input; //nothing to wrap
		else if (input - low_bound >= 0)
			return (fmod((double)input  - low_bound, fabs((double)low_bound - high_bound)) + low_bound);
		else
			return (-1.0 * fmod(-1.0 * (input - low_bound), fabs((double)low_bound - high_bound)) + high_bound);
	}

		
	/** A fast routine for wrapping around the range once.  This is faster than doing an expensive module, where you know the range of the input
	will not equal or exceed twice the range. */
	template<class T>
	T WrapOnce(T input, const T low_bound, const T high_bound)
	{
		if ((input >= low_bound) && (input < high_bound))
			return input;
		else if (input >= high_bound)
			return ((low_bound - 1) + (input - high_bound));
		else
			return ((high_bound + 1) - (low_bound - input));
	}


	/** This routine folds numbers into the data range */
	template<typename T>
	T Fold(T input, const T low_bound, const T high_bound)
	{
		double foldRange;
		
		if ((input >= low_bound) && (input <= high_bound))
			return input; //nothing to fold
		else {
			foldRange = 2 * fabs((double)low_bound - high_bound);
			return fabs(remainder(input - low_bound, foldRange)) + low_bound;
		}
	}

		
	/** A utility for scaling one range of values onto another range of values. */
	template<class T>
	static T Scale(T value, T inlow, T inhigh, T outlow, T outhigh)
	{
		double inscale, outdiff;
		
		inscale = 1 / (inhigh - inlow);
		outdiff = outhigh - outlow;
		
		value = (value - inlow) * inscale;
		value = (value * outdiff) + outlow;
		return(value);
	}
	
	
	/** Rounding utility. */
	template<class T>
	auto Round(T value)
	{
		if (value > 0)
			return((long)(value + 0.5));
		else
			return((long)(value - 0.5));
	}


}  // namespace Jamoma
