/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Defines multiple interpolation algorithms
 
	@author 	Timothy Place, Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {
    /** Defines several functions for <a href="http://en.wikipedia.org/wiki/Interpolation">interpolating</a> between discrete data points such as those found in an array or matrix.
     These methods are commonly used in digital audio whenever we alter the rate at which a signal is read.
     These functions require known discrete values to be passed by reference along with a double between 0 and 1 representing the fractional location desired.
     They return the interpolated value.
     */
	namespace Interpolator {
		
		
		/**	Shared base class for all interpolation types.	*/
		class Base {
		protected:
			constexpr Base() noexcept {};
		};
		
	
		/**	No interpolation always returns the first sample passed to it 
            @param x0		Unused sample value
            @param x1		Sample value that will be returned
            @param x2		Unused sample value
            @param x3		Unused sample value
            @param delta	Unused fractional location
            @return         The interpolated value
         */
		template<class T>
		class None : Base {
		public:
			static const int 	delay = 0;
			
            // NW: will this version ever be used?
			constexpr T operator()(T x1) noexcept {
				return x1;
			}
            
            constexpr T operator()(T x1, T x2, double delta) noexcept {
                return x1;
            }
            
            constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
                return x1;
            }
		};
                
        /**	Nearest interpolation returns the closest sample by rounding the delta up or down. 
            @param x0		Unused sample value
            @param x1		Returned sample value when rounding down
            @param x2		Returned sample value when rounding up
            @param x3		Unused sample value
            @param delta	Fractional location between x1 and x2 @n
                            delta < 0.5 => x1 @n
                            delta >= 0.5 => x2
            @return         The interpolated value
         */
        template<class T>
        class Nearest : Base {
        public:
            static const int 	delay = 0;
            
            // NW: will this version ever be used?
            constexpr T operator()(T x1) noexcept {
                return x1;
            }
            
            constexpr T operator()(T x1, T x2, double delta) noexcept {
                T out = delta < 0.5 ? x1 : x2;
                return out;
            }
            
            constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
                T out = delta < 0.5 ? x1 : x2;
                return out;
            }
        };

		/** Linear interpolation.
            @param x0		Unused sample value
            @param x1		Sample value at prior integer index
			@param x2		Sample value at next integer index
            @param x3		Unused sample value
			@param delta 	Fractional location between x1 (delta=0) and x2 (delta=1)
			@return			The interpolated value
		 */
		template<class T>
		class Linear : Base {
		public:
			static const int 	delay = 1;
			
			constexpr T operator()(T x1, T x2, double delta) noexcept {
				return x1 + delta * (x2-x1);
			}
            
            constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
                // NW: ideally we would call the operator above to remain DRY, but I could not get syntax right
                return x1 + delta * (x2-x1);
            }
		};
                
        /** Allpass interpolation
         Testing shows this algorithm will become less accurate the more points it computes between two known samples.
         Also, because it uses an internal history, the reset() function should be used when switching between non-continuous segments of sampled audio data.
         @param x0		Unused sample value
         @param x1		Sample value at prior integer index
         @param x2		Sample value at next integer index
         @param x3		Unused sample value
         @param delta 	Fractional location between x1 (delta=0) and x2 (delta=1) @n
                        Be aware that delta=1.0 may not return the exact value at x2 given the nature of this algorithm.
         @return			The interpolated value
         */
        template<class T>
        class Allpass : Base {
        public:
            static const int 	delay = 1;
            
            constexpr T operator()(T x1, T x2, double delta) noexcept {
                T out = x1 + delta * (x2-mY1);
                mY1 = out;
                return out;
            }
            
            constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
                // NW: ideally we would call the operator above to remain DRY, but I could not get syntax right
                T out = x1 + delta * (x2-mY1);
                mY1 = out;
                return out;
            }
            
            void reset() {
                mY1 = T(0.0);
            }
            
        private:
            T mY1 = T(0.0);
        };
		

		/** Cosine interpolation
            @param x0		Unused sample value
            @param x1		Sample value at prior integer index
			@param x2		Sample value at next integer index
            @param x3		Unused sample value
			@param delta 	Fractional location between x1 (delta=0) and x2 (delta=1)
			@return			The interpolated value
		 */
		template<class T>
		class Cosine : Base {
		public:
			static const int 	delay = 1;
			
			constexpr T operator()(T x1, T x2, double delta) noexcept {
				T a = 0.5 * (1.0 - cos(delta * M_PI));
				return x1 + a * (x2-x1);
			}
            
            constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
                // NW: ideally we would call the operator above to remain DRY, but I could not get syntax right
                T a = 0.5 * (1.0 - cos(delta * M_PI));
                return x1 + a * (x2-x1);
            }
		};

		
		/** Cubic interpolation
			@param x0		Sample value at integer index prior to x0
			@param x1		Sample value at prior integer index
			@param x2		Sample value at next integer index
			@param x3		Sample value at integer index after x2
			@param delta	Fractional location between x1 (delta=0) and x2 (delta=1)
			@return		The interpolated value
		 */
		template<class T>
		class Cubic : Base {
		public:
			static const int 	delay = 3;
			
			constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
                double delta2 = delta*delta;
                T a = x3 - x2 - x0 + x1;
                T b = x0 - x1 - a;
                T c = x2 - x0;
                return a*delta*delta2 + b*delta2 + c*delta + x1;
			}
		};
		
		
		/** Spline interpolation based on the Breeuwsma catmull-rom spline
			@param x0	Sample value at integer index prior to x
			@param x1	Sample value at prior integer index
			@param x2	Sample value at next integer index
			@param x3	Sample value at integer index after y
			@param delta	Fractional location between x1 (delta=0) and x2 (delta=1)
			@return		The interpolated value.
		 */
		template<class T>
		class Spline : Base {
		public:
			static const int 	delay = 3;

			constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
				T delta2 = delta*delta;
				T f0 = -0.5*x0 + 1.5*x1 - 1.5*x2 + 0.5*x3;
				T f1 = x0 - 2.5*x1 + 2.0*x2 - 0.5*x3;
				T f2 = -0.5*x0 + 0.5*x2;
				return f0*delta*delta2 + f1*delta2 + f2*delta + x1;
			}
		};
		
		
		/** Hermite interpolation
            When bias and tension are both set to 0.0, this algorithm is equivalent to Spline.
			@param x0	Sample value at integer index prior to x
			@param x1	Sample value at prior integer index
			@param x2	Sample value at next integer index
			@param x3	Sample value at integer index after y
			@param delta	Fractional location between x1 (delta=0) and x2 (delta=1)
			@return		The interpolated value.
		 */
		template<class T>
		class Hermite : Base {
		public:
			static const int 	delay = 3;
			double				bias = 0.0;		// attribute
			double				tension = 0.0;	// attribute

			constexpr T operator()(T x0, T x1, T x2, T x3, double delta) noexcept {
				T delta2 = delta*delta;
				T delta3 = delta*delta2;
				T bp = 1+bias;
				T bm = 1-bias;
				T mt = (1-tension)*0.5;
				T m0 = ((x1-x0)*bp + (x2-x1)*bm) * mt;
				T m1 = ((x2-x1)*bp + (x3-x2)*bm) * mt;
				T a0 = 2*delta3 - 3*delta2 + 1;
				T a1 = delta3 - 2*delta2 + delta;
				T a2 = delta3 - delta2;
				T a3 = -2*delta3 + 3*delta2;
				return a0*x1 + a1*m0 + a2*m1 + a3*x2;
			}
		};
		
	}	// namespace Interpolator
}  // namespace Jamoma
