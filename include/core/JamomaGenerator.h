/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generator Algorithms
	
	@details 	Generator Algorithms for use with std::generate.
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {
	namespace Generator {
	
        
		template <typename T>
		class UnipolarRamp {
		public:
			UnipolarRamp (int size)
			: mCycleSize(size)
			{
                //TODO: we need way to protect against zero. static_assert did not work.
            }
			
			T operator()() {
				++mCurrent;
				return T(mCurrent) / mCycleSize;
			}
			
		private:
			int mCurrent = -1;
			int mCycleSize; // required by constructor
		};
		
		
		template <typename T>
		class Sine {
		public:
			Sine (int size)
			: mCycleSize(size)
            {
                //TODO: we need way to protect against zero. static_assert did not work.
            }
			
			T operator()() {
				++mCurrent;
				auto output = std::sin(mCurrent * kTwoPi / mCycleSize);
				return T(output);
			}
			
		private:
			int mCurrent = -1;
			int mCycleSize; // required by constructor
		};
		
		
		template <typename T>
		class Triangle {
		public:
			Triangle (int size)
			: mCycleSize(size)
            {
                //TODO: we need way to protect against zero. static_assert did not work.
            }
			
			T operator()() {
				T out = 0.0;
				++mCurrent;
				
				if (mCurrent <= mCycleSize/4)
					out = 4.0 * mCurrent / mCycleSize;
				else if (mCurrent >= 3 * mCycleSize / 4)
					out = -4.0 + 4.0 * mCurrent / mCycleSize;
				else
					out = 2.0 - 4.0 * mCurrent / mCycleSize;
				return out;
			}
			
		private:
			int mCurrent = -1;
			int mCycleSize; // required by constructor
		};
	
	} // namespace Generator
} // namespace Jamoma
