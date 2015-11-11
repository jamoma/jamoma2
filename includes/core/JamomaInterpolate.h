/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Interpolation implementations

	@details	Defines several functions for <a href="http://en.wikipedia.org/wiki/Interpolation">interpolating</a> between discrete data points such as those found in an array or matrix. 
				These methods are commonly used in digital audio whenever we alter the rate at which a signal is read.
				These functions require known discrete values to be passed by reference along with a double between 0 and 1 representing the fractional location desired. 
				They return the interpolated value.
 
	@author 	Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.
 */

#pragma once


namespace Jamoma {
	namespace Interpolation {
		
		
		class Generic {};
		
	
		
		template<class T>
		class None : Generic {
		public:
			static const int 	delay = 0;
			
			T operator()(T x0) {
				return x0;
			}
			
		};

		
		/** Linear interpolation.
			@param x0		Sample value at prior integer index
			@param x1		Sample value at next integer index
			@param delta 	Linear interpolation between x0 (delta=0) and x1 (delta=1)
			@return			The interpolated value.

			@seealso		TTInterpolateCosine
			@seealso		TTInterpolateCubic
			@seealso		TTInterpolateSpline
			@seealso		TTInterpolateHermite
		 */
		template<class T>
		class Linear : Generic {
		public:
			static const int 	delay = 1;
			
			T operator()(T x0, T x1, double delta) {
				return x0 + delta * (x1-x0);
			}
			
		};
		

		/** Cosine interpolation
			@param x0		Sample value at prior integer index
			@param x1		Sample value at next integer index
			@param delta 	Fractional location between x(0) and x(1)
			@return			The interpolated value
		 */
		template<class T>
		class Cosine : Generic {
		public:
			static const int 	delay = 1;
			
			T operator()(T x0, T x1, double delta) {
				T a = 0.5 * (1.0 - cos(delta * kPi));
				return x0 + a * (x1-x0);
			}
			
		};

		
		/** Cubic interpolation
			This interpolation algorithms calculate the coefficients a, b, c, d
			of the 3rd order polynomial

			f(delta)	= a*aDelta^3 + b*aDelta^2 + c*aDelta + d
			= ( (a*aDelta + b )*aDelta + c)*aDelta + d)

			so that the function fulfill the following four conditions:

			-# f(0)  = x1 @n
			-# f(1)  = x2 @n
			-# f'(0) = (x2-x0)/2 @n
			-# f'(1) = (x3-x1)/2

			The two last conditions use a symetric estimate of the difference at the end points
			of the region to interpolate over: 0 ≤ aDelta ≤ 1

			These asumptions ensure that the resulting interpolated function, when moving over several
			subsequent sections, is:

			-# Continuous (no sudden jump)
			-# Has a continuous derivative (no break pints with hard edges)

			However, the 2nd order derivate will generally be discontinuous on the points connecting two sections.

			@param x0		Sample value at integer index prior to x0
			@param x1		Sample value at prior integer index
			@param x2		Sample value at next integer index
			@param x3		Sample value at integer index after x2
			@param aDelta	Fractional location where we want to do the interpolation. @n
							aDelta = 0 => interpolatedeValue = x1 @n
							aDelta = 1 => interpolatedeValue = x2
			@return		The interpolated value.
		 */
		template<class T>
		class Cubic : Generic {
		public:
			static const int 	delay = 3;
			
			T operator()(T x0, T x1, T x2, T x3, double delta) {
				T a = (-x0 + 3.*x1 - 3*x2 + x3)*0.5;
				T b = x0 - 2.5*x1 + 2.*x2 - 0.5*x3;
				T c = (x2-x0)*0.5;
				return ( (a*delta + b)*delta + c)*delta + x1;
			}
			
		};
		
		
		/** Spline interpolation based on the Breeuwsma catmull-rom spline
			@param w	Sample value at integer index prior to x
			@param x	Sample value at prior integer index
			@param y	Sample value at next integer index
			@param z	Sample value at integer index after y
			@param a	Fractional location between x (0) and y (1)
			@return		The interpolated value.
		 */
		template<class T>
		class Spline : Generic {
		public:
			static const int 	delay = 3;

			T operator()(T w, T x, T y, T z, double a) {
				T a2 = a*a;
				T f0 = -0.5*w + 1.5*x - 1.5*y + 0.5*z;
				T f1 = w - 2.5*x + 2.0*y - 0.5*z;
				T f2 = -0.5*w + 0.5*y;
				return f0*a*a2 + f1*a2 + f2*a + x;
			}
		};
		
		
		/** Hermite interpolation
			@param w	Sample value at integer index prior to x
			@param x	Sample value at prior integer index
			@param y	Sample value at next integer index
			@param z	Sample value at integer index after y
			@param a	Fractional location between x (0) and y (1)
			@return		The interpolated value.
		 */
		template<class T>
		class Hermite : Generic {
		public:
			static const int 	delay = 3;
			double				bias = 0.0;		// attribute
			double				tension = 0.0;	// attribute

			T operator()(T w, T x, T y, T z, double a) {
				T aa = a*a;
				T aaa = a*aa;
				T bp = 1+bias;
				T bm = 1-bias;
				T mt = (1-tension)*0.5;
				T m0 = ((x-w)*bp + (y-x)*bm) * mt;
				T m1 = ((y-x)*bp + (z-y)*bm) * mt;
				T a0 = 2*aaa - 3*aa + 1;
				T a1 = aaa - 2*aa + a;
				T a2 = aaa - aa;
				T a3 = -2*aaa + 3*aa;
				return a0*x + a1*m0 + a2*m1 + a3*y;
			}
		};
		
	}	// namespace Interpolation
}  // namespace Jamoma
