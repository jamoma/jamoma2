/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Generator Algorithms
	
	@author		Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {
    /** Defines several functions for use with <a href="http://en.cppreference.com/w/cpp/algorithm/generate">std::generate</a> to fill vectors with common shapes used in computer sound.
     */
	namespace Generator {
        
        /** Generates a line from -1 to 1 with consistent slope
         @param T       render output as this datatype. algorithm was designed to assume the use of floating point.
         @param size    size of the target vector
         */
        template <typename T>
        class Ramp {
        public:
            Ramp (int size)
            : mCycleSize(size)
            {
                //TODO: we need way to protect against zero. static_assert did not work.
            }
            
            T operator()() {
                ++mCurrent;
                return ( T(mCurrent) * 2.0 / mCycleSize) - 1.0;
            }
            
        private:
            int mCurrent = -1;
            int mCycleSize; // required by constructor
        };
        
        /** Generates a line from 0 to 1 with consistent slope
         @param T       render output as this datatype. algorithm was designed to assume the use of floating point.
         @param size    size of the target vector
         */
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
		
        /** Generates a sine wave constrained between -1 to 1
         @param T       render output as this datatype. algorithm was designed to assume the use of floating point.
         @param size    size of the target vector
         */
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
		
        /** Generates a triangle wave constrained between -1 to 1
         @param T       render output as this datatype. algorithm was designed to assume the use of floating point.
         @param size    size of the target vector
         */
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
        
        /** Generates a triangle wave constrained between 0 to 1
         @param T       render output as this datatype. algorithm was designed to assume the use of floating point.
         @param size    size of the target vector
         */
        template <typename T>
        class UnipolarTriangle {
        public:
            UnipolarTriangle (int size)
            : mCycleSize(size)
            {
                //TODO: we need way to protect against zero. static_assert did not work.
            }
            
            T operator()() {
                T out = 0.0;
                ++mCurrent;
                
                if (mCurrent <= mCycleSize/4)
                    out = 2.0 * mCurrent / mCycleSize;
                else if (mCurrent >= 3 * mCycleSize / 4)
                    out = -2.0 + 2.0 * mCurrent / mCycleSize;
                else
                    out = 1.0 - 2.0 * mCurrent / mCycleSize;
                return 0.5 + out;
            }
            
        private:
            int mCurrent = -1;
            int mCycleSize; // required by constructor
        };
	
	} // namespace Generator
} // namespace Jamoma
