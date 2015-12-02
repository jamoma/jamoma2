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
        testHermite();
        testSpline();
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
        Jamoma::Interpolation::Linear<Jamoma::Sample> my_interp;
        
		auto 	x0 = -1.0;
		auto	x1 =  2.0;
	
        // The following output was generated using the Octave code
        // in InterpolationTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputLinear = {
            -0.953125,
            -0.90625,
            -0.859375,
            -0.8125,
            -0.765625,
            -0.71875,
            -0.671875,
            -0.625,
            -0.578125,
            -0.53125,
            -0.484375,
            -0.4375,
            -0.390625,
            -0.34375,
            -0.296875,
            -0.25,
            -0.203125,
            -0.15625,
            -0.109375,
            -0.0625,
            -0.015625,
            0.03125,
            0.078125,
            0.125,
            0.171875,
            0.21875,
            0.265625,
            0.3125,
            0.359375,
            0.40625,
            0.453125, 
            0.5, 
            0.546875, 
            0.59375, 
            0.640625, 
            0.6875, 
            0.734375, 
            0.78125, 
            0.828125, 
            0.875, 
            0.921875, 
            0.96875, 
            1.015625, 
            1.0625, 
            1.109375, 
            1.15625, 
            1.203125, 
            1.25, 
            1.296875, 
            1.34375, 
            1.390625, 
            1.4375, 
            1.484375, 
            1.53125, 
            1.578125, 
            1.625, 
            1.671875, 
            1.71875, 
            1.765625, 
            1.8125, 
            1.859375, 
            1.90625, 
            1.953125, 
            2
        };
	
        Jamoma::Sample temp = 0.0;
        Jamoma::Sample tempExpected = 0.0;
        double delta = 0.0;
        
        for (int i = 0; i < expectedOutputLinear.size(); i++) {
            delta = (i + 1.0) / 64.0;
            temp = my_interp(x0,x1,delta);
            tempExpected = expectedOutputLinear[i];
            if (! mTest->compare(temp, tempExpected, true, 8) ) {
                badSampleCount++;
                std::cout << "sample " << i << " had a difference of " << std::fabs(temp - tempExpected) << std::endl;
            }
        }

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
    
    void testHermite() {
        int		badSampleCount = 0;
        Jamoma::Interpolation::Hermite<Jamoma::Sample> my_interp;
        
        auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        auto    x3 =  4.0;
        
        // The following output was generated using the Octave code
        // in InterpolationTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputHermite = {
            1.999275207519531,
            1.99713134765625,
            1.993614196777344,
            1.98876953125,
            1.982643127441406,
            1.97528076171875,
            1.966728210449219,
            1.95703125,
            1.946235656738281,
            1.93438720703125,
            1.921531677246094,
            1.90771484375,
            1.892982482910156,
            1.87738037109375,
            1.860954284667969,
            1.84375,
            1.825813293457031,
            1.80718994140625,
            1.787925720214844,
            1.76806640625,
            1.747657775878906,
            1.72674560546875,
            1.705375671386719,
            1.68359375,
            1.661445617675781,
            1.63897705078125,
            1.616233825683594,
            1.59326171875,
            1.570106506347656,
            1.54681396484375,
            1.523429870605469,
            1.5,
            1.476570129394531,
            1.45318603515625,
            1.429893493652344,
            1.40673828125,
            1.383766174316406,
            1.36102294921875,
            1.338554382324219,
            1.31640625, 
            1.294624328613281, 
            1.27325439453125, 
            1.252342224121094, 
            1.23193359375, 
            1.212074279785156, 
            1.19281005859375, 
            1.174186706542969, 
            1.15625, 
            1.139045715332031, 
            1.12261962890625, 
            1.107017517089844, 
            1.09228515625, 
            1.078468322753906, 
            1.06561279296875, 
            1.053764343261719, 
            1.04296875, 
            1.033271789550781, 
            1.02471923828125, 
            1.017356872558594, 
            1.01123046875, 
            1.006385803222656, 
            1.00286865234375, 
            1.000724792480469, 
            1
        };
        
        mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
    }
    
    void testSpline() {
        int		badSampleCount = 0;
        Jamoma::Interpolation::Spline<Jamoma::Sample> my_interp;
        
        auto 	x0 = -1.0;
        auto	x1 =  2.0;
        auto    x2 =  1.0;
        auto    x3 =  4.0;
        
        // The following output was generated using the Octave code
        // in InterpolationTargetOutput.m by NW
        Jamoma::SampleVector expectedOutputSpline = {
            1.994308471679688,
            1.9876708984375,
            1.980117797851562,
            1.9716796875,
            1.962387084960938,
            1.9522705078125,
            1.941360473632812,
            1.9296875,
            1.917282104492188,
            1.9041748046875,
            1.890396118164062,
            1.8759765625,
            1.860946655273438,
            1.8453369140625,
            1.829177856445312,
            1.8125,
            1.795333862304688,
            1.7777099609375,
            1.759658813476562,
            1.7412109375,
            1.722396850585938,
            1.7032470703125,
            1.683792114257812,
            1.6640625,
            1.644088745117188,
            1.6239013671875,
            1.603530883789062,
            1.5830078125,
            1.562362670898438,
            1.5416259765625,
            1.520828247070312,
            1.5,
            1.479171752929688,
            1.4583740234375,
            1.437637329101562,
            1.4169921875,
            1.396469116210938,
            1.3760986328125,
            1.355911254882812,
            1.3359375, 
            1.316207885742188, 
            1.2967529296875, 
            1.277603149414062, 
            1.2587890625, 
            1.240341186523438, 
            1.2222900390625, 
            1.204666137695312, 
            1.1875, 
            1.170822143554688, 
            1.1546630859375, 
            1.139053344726562, 
            1.1240234375, 
            1.109603881835938, 
            1.0958251953125, 
            1.082717895507812, 
            1.0703125, 
            1.058639526367188, 
            1.0477294921875, 
            1.037612915039062, 
            1.0283203125, 
            1.019882202148438, 
            1.0123291015625, 
            1.005691528320312, 
            1
        };
        
        mTest->TEST_ASSERT("Bad Sample Count", badSampleCount == 0);
    }

};


int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<InterpolationTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
