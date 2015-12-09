/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for Interpolation classes
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class InterpolationTest {
	
	Jamoma::UnitTest<InterpolationTest>*	mTest;
	
public:
	InterpolationTest(Jamoma::UnitTest<InterpolationTest>* test)
	: mTest(test)
	{
		testLinear();
		testCosine();
		testCubic();
	}

	
	template <class InterpolationType>
	auto interpolateAndTest(Jamoma::Sample x0, Jamoma::Sample x1, Jamoma::Sample aDelta, Jamoma::Sample anExpectedValue) {
		InterpolationType	interpolator;
		auto				interpolatedValue = interpolator(x0, x1, aDelta);
		auto				result = mTest->compare(interpolatedValue , anExpectedValue);
		
		if (result == false)
			mTest->log("BAD INTERPOLATION @ delta=%.5f  ( value=%.10f   expected=%.10f )", aDelta, interpolatedValue, anExpectedValue);
		return result;
	}
	
	// TODO: way to make a single function template that is variadic?
	template <class InterpolationType>
	auto interpolateAndTest(float x0, float x1,float x2, float x3, float aDelta, float anExpectedValue) {
		InterpolationType	interpolator;
		auto				interpolatedValue = interpolator(x0, x1, x2, x3, aDelta);
		auto				result = mTest->compare(interpolatedValue , anExpectedValue);
		
		if (result == false)
			mTest->log("BAD INTERPOLATION @ delta=%.5f  ( value=%.10f   expected=%.10f )", aDelta, interpolatedValue, anExpectedValue);
		return result;
	}

	
	
	void testLinear() {
		int		badSampleCount = 0;
		auto 	x0 =  3.0;
		auto	x1 = -1.0;
	
		mTest->log("");
		mTest->log("Testing linear interpolation");
	
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Linear<Jamoma::Sample>>(x0, x1, 0.00,  3.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Linear<Jamoma::Sample>>(x0, x1, 0.25,  2.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Linear<Jamoma::Sample>>(x0, x1, 0.50,  1.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Linear<Jamoma::Sample>>(x0, x1, 0.75,  0.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Linear<Jamoma::Sample>>(x0, x1, 1.00, -1.0);

		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);		
	}
	
	
	void testCosine() {
		int		badSampleCount = 0;
		auto 	x0 =  3.0;
		auto	x1 = -1.0;
		
		mTest->log("");
		mTest->log("Testing cosine interpolation");
		
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cosine<double>>(x0, x1, 0.00,     3.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cosine<double>>(x0, x1, 1.0/3.0,  2.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cosine<double>>(x0, x1, 0.50,     1.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cosine<double>>(x0, x1, 2.0/3.0,  0.00000000000000044408920985006262);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cosine<double>>(x0, x1, 1.00,    -1.0);
		
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
	}
	
	
	/*	We perform the interpolation on four values of the following function:
		g(delta) = cos (PI*delta) + delta + 1

		This gives the following input values to the interpolating function:

		g(-1) = -1
		g( 0) =  2
		g( 1) =  1
		g( 2) =  4

		The difference is calculated as
		∆g(delta) = (g(delta+1)-g(delta-1)) / 2

		This leads to:

		∆g(0) = ( 1 -(-1) )/2 = 1
		∆g(1) = ( 4 - 2)/2 = 1

		The cubic interpolation function f(delta) is then required to fullfil the following four conditions:

		(A) f( 0) =  2
		(B) f( 1) =  1
		(C) f'(0) = 1
		(D) f'(1) = 1

		Analytically, when solved, these four conditions are fulfilled by the following 3rd order polynomial:
		f(delta) = 4 delta^3 - 6 delta^2 + delta + 2

		The following test compares interpolated values to expected values for this function.
	 */
	void testCubic() {
		int		badSampleCount = 0;
		float	x0 = -1.0;
		float	x1 =  2.0;
		float	x2 =  1.0;
		float	x3 =  4.0;
		
		mTest->log("");
		mTest->log("Testing cubic interpolation");
		
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cubic<float>>(x0, x1, x2, x3, -1.00, -9.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cubic<float>>(x0, x1, x2, x3,  0.00,  2.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cubic<float>>(x0, x1, x2, x3,  1.00,  1.0);
		badSampleCount += !interpolateAndTest<Jamoma::Interpolation::Cubic<float>>(x0, x1, x2, x3,  2.00, 12.0);
		
		mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
	}

};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<InterpolationTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
