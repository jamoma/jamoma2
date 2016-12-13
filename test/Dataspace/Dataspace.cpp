/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for the Dataspace class
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Jamoma.h"

using namespace Jamoma;



SCENARIO( "Angle Dataspace is used with type `double`" ) {

	GIVEN( "Conversion is to unit `radian`" ) {

		Dataspace::Angle<double, Dataspace::AngleUnit::radian> radianConverter;

		WHEN( "unspecified unit is assumed to be the native unit (radian)" ) {
			auto y = radianConverter(0.5);
			REQUIRE( y == Approx(0.5) );
		}
		AND_WHEN( "angle is expressed as radians" ) {
			auto y = radianConverter(0.6, Dataspace::AngleUnit::radian);
			REQUIRE( y == Approx(0.6) );
		}
		AND_WHEN( "angle is expressed as rad" ) {
			auto y = radianConverter(0.7, Dataspace::AngleUnit::rad);
			REQUIRE( y == Approx(0.7) );
		}
		AND_WHEN( "angle is expressed as degree" ) {
			auto y = radianConverter(180., Dataspace::AngleUnit::degree);
			REQUIRE( y == Approx(kPi) );
		}
		AND_WHEN( "angle is expressed as deg" ) {
			auto y = radianConverter(90., Dataspace::AngleUnit::degree);
			REQUIRE( y == Approx(kPi*0.5) );
		}
	}
	
	GIVEN( "Conversion is to unit `radian`" ) {
		Dataspace::Angle<double, Dataspace::AngleUnit::degree> degreeConverter;
		
		WHEN( "radian-to-degree conversion requested using enum unit" ) {
			auto y = degreeConverter(kPi*0.5, Dataspace::AngleUnit::radian);
			REQUIRE( y == Approx(90.0) );
		}
		AND_WHEN( "rad-to-degree conversion requested using string unit" ) {
			auto y = degreeConverter(kPi*0.5, "rad");
			REQUIRE( y == Approx(90.0) );
		}
	}
	
}



SCENARIO( "Distance Dataspace is used with type `double`" ) {
	
	GIVEN( "Conversion is to unit `meters`" ) {
		
		Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::meters> metersConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (meters)" ) {
			auto y = metersConverter(0.5);
			REQUIRE( y == Approx(0.5) );
		}
		AND_WHEN( "centimeter to meter using enum unit" ) {
			auto y = metersConverter(123.4, Dataspace::DistanceUnit::centimeters);
			REQUIRE( y == Approx(1.234));
		}
		AND_WHEN( "cm to meter using enum unit" ) {
			auto y = metersConverter(123.4, Dataspace::DistanceUnit::cm);
			REQUIRE( y == Approx(1.234));
		}
		AND_WHEN( "feet to meter using enum unit" ) {
			// Expected value according to Google search: "6 feet to meter"
			// The Google result hasn't much resolution, but is sufficient to indicate that we're OK
			auto y =  roundf(metersConverter(6.0, Dataspace::DistanceUnit::feet) * 10000.) / 10000.;
			REQUIRE( y == Approx(1.8288));
		}
		AND_WHEN( "feetSign (') to meter using enum unit" ) {
			auto y = roundf(metersConverter(6.0, Dataspace::DistanceUnit::feetSign) * 10000.) / 10000.;
			REQUIRE( y == Approx(1.8288));
		}
		
		AND_WHEN("inches to meter using enum unit" ) {
			// Expected value according to Google search: "15 inch to meter"
			// The Google result hasn't much resolution, but is sufficient to indicate that we're OK
			auto y = roundf(metersConverter(15.0, Dataspace::DistanceUnit::inches) * 1000.) / 1000.;
			REQUIRE( y == Approx(0.381));
		}
		AND_WHEN( "inchesSign (\") to meter using enum unit" ) {
			auto y = roundf(metersConverter(15.0, Dataspace::DistanceUnit::inches) * 1000.) / 1000.;
			REQUIRE( y == Approx(0.381));
		}

	}
	
	GIVEN( "Conversion is to unit `centimeters`" ) {
		WHEN( "conversion requested using enum unit" ) {
			Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::centimeters>	centimetersConverter;
			auto y = centimetersConverter(1.234, Dataspace::DistanceUnit::meters);
			REQUIRE( y == Approx(123.4) );
		}
		AND_WHEN( "conversion requested using abbreviated enum unit" ) {
			Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::cm>	cmConverter;
			auto y = cmConverter(1.234, Dataspace::DistanceUnit::meters);
			REQUIRE( y == Approx(123.4) );
		}
	}
	
	GIVEN( "Conversion is to unit `feet`" ) {
		WHEN( "conversion requested using enum unit" ) {
			Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::feet>	feetConverter;
			auto y = feetConverter(1.8288, Dataspace::DistanceUnit::meters);
			y = roundf(y);
			REQUIRE( y == Approx(6.0) );
		}
		AND_WHEN( "conversion requested using abbreviated enum unit" ) {
			Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::feetSign>	feetSignConverter;
			auto y = roundf(feetSignConverter(1.8288, Dataspace::DistanceUnit::meters));
			REQUIRE( y == Approx(6.0) );
		}
	}

	GIVEN( "Conversion is to unit `inches`" ) {
		WHEN( "conversion requested using enum unit" ) {
			Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::inches>	inchesConverter;
			auto y = roundf(inchesConverter(0.381, Dataspace::DistanceUnit::meters));
			REQUIRE( y == Approx(15.0) );
		}
		AND_WHEN( "conversion requested using abbreviated enum unit" ) {
			Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::inchesSign>	inchesSignConverter;
			auto y = roundf(inchesSignConverter(0.381, Dataspace::DistanceUnit::meters));
			REQUIRE( y == Approx(15.0) );
		}
	}
	
}



SCENARIO( "Gain Dataspace is used with type `double`" ) {
	
	GIVEN( "Conversion is to unit `linear`" ) {
		
		Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::linear> linearConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (linear)" ) {
			auto y = linearConverter(0.5);
			REQUIRE( y == Approx(0.5) );
		}
		AND_WHEN( "-12.0 decibel to meter using enum unit" ) {
			auto y = linearConverter(-12.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(0.25118864315095796));
		}
		AND_WHEN( "-6.0 decibel to linear using enum unit" ) {
			auto y = linearConverter(-6.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(0.50118723362727224));
		}
		AND_WHEN( "0.0 decibel to linear using enum unit" ) {
			auto y = linearConverter(0.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(1.0));
		}
		AND_WHEN( "-10.0 midigain (out of range) to linear using enum unit" ) {
			auto y =  linearConverter(-10.0, Dataspace::GainUnit::midigain);
			REQUIRE( y == Approx(0.0));
		}
		AND_WHEN( "0 midigain to linear using enum unit" ) {
			auto y =  linearConverter(0.0, Dataspace::GainUnit::midigain);
			REQUIRE( y == Approx(0.0));
		}
		AND_WHEN( "100 midigain to linear using enum unit" ) {
			auto y =  linearConverter(100.0, Dataspace::GainUnit::midigain);
			REQUIRE( y == Approx(1.0));
		}
	}

	GIVEN( "Conversion is to unit `dB`" ) {
		
		Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::db> dbConverter;
		
		WHEN( "0 linear to dB using enum unit" ) {
			auto y = dbConverter(0.0, Dataspace::GainUnit::linear);
			REQUIRE( y == Approx(-96.0) );
		}
		AND_WHEN( "1.0 linear to dB using enum unit" ) {
			auto y = dbConverter(1.0, Dataspace::GainUnit::linear);
			REQUIRE( y == Approx(0.0) );
		}
		AND_WHEN( "2.0 linear to dB using enum unit" ) {
			auto y = dbConverter(2.0, Dataspace::GainUnit::linear);
			REQUIRE( y == Approx(6.0205999132796242) );
		}
		AND_WHEN( "0 midigain to dB using abbreviated enum unit" ) {
			auto y = dbConverter(0.0, Dataspace::GainUnit::midigain);
			REQUIRE( y == Approx(-96.0) );
		}
		AND_WHEN( "100 midigain to dB using abbreviated enum unit" ) {
			auto y = dbConverter(100.0, Dataspace::GainUnit::midigain);
			REQUIRE( y == Approx(0.0) );
		}
		AND_WHEN( "127 midigain to dB using abbreviated enum unit" ) {
			auto y = dbConverter(127.0, Dataspace::GainUnit::midigain);
			REQUIRE( y == Approx(12.0) );
		}
		AND_WHEN( "-97 dB(out of range) to dB using abbreviated enum unit" ) {
			auto y = dbConverter(-97.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(-96.0) );
		}
	}
	
	GIVEN( "Conversion is to unit `midigain`" ) {
		
		Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::midigain> midigainConverter;
		
		WHEN( "0.0 linear til midigain using enum unit" ) {
			auto y = midigainConverter(0.0, Dataspace::GainUnit::linear);
			REQUIRE( y == Approx(0.0) );
		}
		AND_WHEN( "1.0 linear til midigain using enum unit" ) {
			auto y = midigainConverter(1.0, Dataspace::GainUnit::linear);
			REQUIRE( y == Approx(100.0) );
		}
		AND_WHEN( "-200 dB (below low dB threshold) til midigain using enum unit" ) {
			auto y = midigainConverter(-200.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(0.0) );
		}
		AND_WHEN( "-96 dB til midigain using enum unit" ) {
			auto y = midigainConverter(-96.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(0.0) );
		}
		AND_WHEN( "0.0 dB til midigain using enum unit" ) {
			auto y = midigainConverter(0.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(100.0) );
		}
		AND_WHEN( "12.0 dB til midigain using enum unit" ) {
			auto y = midigainConverter(12.0, Dataspace::GainUnit::db);
			REQUIRE( y == Approx(127.0) );
		}
	}
}



SCENARIO( "Position Dataspace is used with type `double`" ) {
	
	using Jamoma::Dataspace::PositionValue;
	
	GIVEN( "Conversion is to unit `xyz`" ) {
		
		Dataspace::Position<double, Dataspace::PositionUnit::xyz> xyzConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (xyz)" ) {
			auto output = xyzConverter( {{ 1.0, 2.0, 3.0 }} );
			REQUIRE( output.size() == 3);
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == Approx(3.0) );
		}
		AND_WHEN( "position is expressed as cart3d" ) {
			// same as 'xyz'
			auto output = xyzConverter( {{ 1.0, 2.0, 3.0 }}, Dataspace::PositionUnit::cart3D);
			REQUIRE( output.size() == 3);
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == Approx(3.0) );
		}
		AND_WHEN( "position is expressed as xy" ) {
			// an extraneous z value is tossed-out
			auto output = xyzConverter( {{ 1.0, 2.0, 3.0 }}, Dataspace::PositionUnit::xy);
			REQUIRE( output.size() == 3);
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == 0.0 );
		}
		AND_WHEN( "position is expressed as cart2d" ) {
			// same as 'xy'
			auto output = xyzConverter( {{ 1.0, 2.0, 3.0 }}, Dataspace::PositionUnit::cart2D);
			REQUIRE( output.size() == 3);
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == 0.0 );
		}
	}
	
	GIVEN( "Conversion is to unit `xy`" ) {
		
		Dataspace::Position<double, Dataspace::PositionUnit::xy> xyConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (xy)" ) {
			auto output = xyConverter( {{ 1.0, 2.0 }} );
			REQUIRE( output.size() == 3);		// still size 3 for the data returned but the extra element is set to zero
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == 0.0 );
		}
		AND_WHEN( "position is expressed as cart2d" ) {
			// same as 'xy'
			auto output = xyConverter( {{ 1.0, 2.0 }}, Dataspace::PositionUnit::cart2D);
			REQUIRE( output.size() == 3);		// still size 3 for the data returned but the extra element is set to zero
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == 0.0 );
		}
		AND_WHEN( "position is expressed as xyz" ) {
			// an extraneous z value is tossed-out
			auto output = xyConverter( {{ 1.0, 2.0, 3.0 }}, Dataspace::PositionUnit::xyz);
			REQUIRE( output.size() == 3);
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == 0.0 );
		}
		AND_WHEN( "position is expressed as cart3d" ) {
			// same as 'xyz'
			auto output = xyConverter( {{ 1.0, 2.0, 3.0 }}, Dataspace::PositionUnit::cart3D);
			REQUIRE( output.size() == 3);
			REQUIRE( output[0] == Approx(1.0) );
			REQUIRE( output[1] == Approx(2.0) );
			REQUIRE( output[2] == 0.0 );
		}
	}
	
}



SCENARIO( "Speed Dataspace is used with type `double`" ) {
	
	GIVEN( "Conversion is to unit `m/s`" ) {
		
		Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::meterPerSecond> meterPerSecondConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (kelvin)" ) {
			auto y = meterPerSecondConverter(20.0);
			REQUIRE( y == Approx(20.0) );
		}
		AND_WHEN( "mi/h to m/s using enum unit" ) {
			auto y = meterPerSecondConverter(50.0, Dataspace::SpeedUnit::milesPerHour);
			REQUIRE( y == Approx(22.35200));
		}
		AND_WHEN( "knot to m/s using enum unit" ) {
			auto y = meterPerSecondConverter(45.0, Dataspace::SpeedUnit::knot);
			REQUIRE( y == Approx(23.15));
		}
		AND_WHEN( "foot to m/s using enum unit" ) {
			auto y = meterPerSecondConverter(20.0, Dataspace::SpeedUnit::footPerSecond);
			REQUIRE( y == Approx(6.09600));
		}
	}
	
	GIVEN( "Conversion is to unit `km/h`" ) {
		
		Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::kilometerPerHour> kilometerPerHourConverter;

		WHEN( "m/s to km/h using enum unit" ) {
			auto y = kilometerPerHourConverter(10.0, Dataspace::SpeedUnit::meterPerSecond);
			REQUIRE( y == Approx(36.0));
		}
	}
	
	GIVEN( "Conversion is to unit `kmph`" ) {
		
		Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::kmph> kmphConverter;
		
		WHEN( "m/s to km/h using enum unit" ) {
			auto y = kmphConverter(10.0, Dataspace::SpeedUnit::meterPerSecond);
			REQUIRE( y == Approx(36.0));
		}
	}
	
	GIVEN( "Conversion is to unit `mi/h`" ) {
		
		Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::milesPerHour> milesPerHourConverter;
		
		WHEN( "m/s to km/h using enum unit" ) {
			auto y = milesPerHourConverter(22.35200, Dataspace::SpeedUnit::meterPerSecond);
			REQUIRE( y == Approx(50.0));
		}
	}
	
	GIVEN( "Conversion is to unit `mi/h`" ) {
		
		Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::knot> knotConverter;
		
		WHEN( "m/s to km/h using enum unit" ) {
			auto y = knotConverter(23.15, Dataspace::SpeedUnit::meterPerSecond);
			REQUIRE( y == Approx(45.0));
		}
	}
	
	GIVEN( "Conversion is to unit `footPerSecond`" ) {
		
		Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::footPerSecond> footPerSecondConverter;
		
		WHEN( "m/s to km/h using enum unit" ) {
			auto y = footPerSecondConverter(6.09600, Dataspace::SpeedUnit::meterPerSecond);
			REQUIRE( y == Approx(20.0));
		}
	}
}



SCENARIO( "Temperature Dataspace is used with type `double`" ) {
	
	GIVEN( "Conversion is to unit `kelvin`" ) {
		
		Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::kelvin> kelvinConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (kelvin)" ) {
			auto y = kelvinConverter(273.15);
			REQUIRE( y == Approx(273.15) );
		}
		AND_WHEN( "0 degress Celsius to Kelvin using enum unit" ) {
			auto y = kelvinConverter(0.0, Dataspace::TemperatureUnit::celsius);
			REQUIRE( y == Approx(273.15));
		}
		AND_WHEN( "32 degress Fahrenheit to Kelvin using enum unit" ) {
			auto y = kelvinConverter(32.0, Dataspace::TemperatureUnit::fahrenheit);
			REQUIRE( y == Approx(273.15));
		}
	}
	
	GIVEN( "Conversion is to unit `celsius`" ) {
		
		Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::celsius> celsiusConverter;
		
		WHEN( "273.15 degress Kelvin to Celsius using enum unit" ) {
			auto y = celsiusConverter(0.0, Dataspace::TemperatureUnit::celsius);
			REQUIRE( y == Approx(0.0));
		}
		AND_WHEN( "32 degress Fahrenheit to Celsius using enum unit" ) {
			auto y = celsiusConverter(32.0, Dataspace::TemperatureUnit::fahrenheit);
			REQUIRE( y == Approx(0.0));
		}
	}
	
	GIVEN( "Conversion is to unit `fahrenheit`" ) {
		
		Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::fahrenheit> fahrenheitConverter;
		
		WHEN( "273.15 degress Kelvin to Fahrenheit using enum unit" ) {
			auto y = fahrenheitConverter(273.15, Dataspace::TemperatureUnit::kelvin);
			REQUIRE( y == Approx(32.0));
		}
		AND_WHEN( "0 degress Celsius to Fahrenheit using enum unit" ) {
			auto y = fahrenheitConverter(0.0, Dataspace::TemperatureUnit::celsius);
			REQUIRE( y == Approx(32.0));
		}
	}

}



SCENARIO( "Time Dataspace is used with type `double`" ) {
	
	GIVEN( "Conversion is to unit `second`" ) {
		
		Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::seconds> secondsConverter;
		
		WHEN( "unspecified unit is assumed to be the native unit (seconds)" ) {
			auto y = secondsConverter(256.0);
			REQUIRE( y == Approx(256.0) );
		}
		AND_WHEN( "Milliseconds to seconds using enum unit" ) {
			auto y = secondsConverter(1234.5, Dataspace::TimeUnit::milliseconds);
			REQUIRE( y == Approx(1.2345));
		}
		
		// TODO: samples to seconds
		
		AND_WHEN( "Hertz to seconds using enum unit" ) {
			auto y = secondsConverter(4.0, Dataspace::TimeUnit::hertz);
			REQUIRE( y == Approx(0.25));
		}
		AND_WHEN( "Beats per minute to seconds using enum unit" ) {
			auto y = secondsConverter(120.0, Dataspace::TimeUnit::bpm);
			REQUIRE( y == Approx(0.5));
		}
		AND_WHEN( "Midi note 57 to seconds using enum unit" ) {
			auto y = secondsConverter(57.0, Dataspace::TimeUnit::midinote);
			REQUIRE( y == Approx(1/220.));
		}
		AND_WHEN( "Midi note 69 to seconds using enum unit" ) {
			auto y = secondsConverter(69.0, Dataspace::TimeUnit::midinote);
			REQUIRE( y == Approx(1/440.));
		}
		AND_WHEN( "5700 cents to seconds using enum unit" ) {
			auto y = secondsConverter(5700.0, Dataspace::TimeUnit::cents);
			REQUIRE( y == Approx(1/220.));
		}
		AND_WHEN( "6900 cents to seconds using enum unit" ) {
			auto y = secondsConverter(6900.0, Dataspace::TimeUnit::cents);
			REQUIRE( y == Approx(1/440.));
		}
		AND_WHEN( "bark to seconds using enum unit" ) {
			auto y = secondsConverter(5.0, Dataspace::TimeUnit::bark);
			REQUIRE( y == Approx(0.001785990780318596));
		}
		AND_WHEN( "mel to seconds using enum unit" ) {
			auto y = secondsConverter(1000.0, Dataspace::TimeUnit::mel);
			REQUIRE( y == Approx(0.0009999781840186604));
		}
		// speed => seconds
		// Rather than checking this, there are tests for speed <=> midi note further down
	}
	
	GIVEN( "Conversion is from unit `second`" ) {
		
		AND_WHEN( "Seconds to milliseconds using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::milliseconds> msConverter;
			auto y = msConverter(1.2345, Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(1234.5));
		}
		
		//  TODO: seconds to samples
		
		AND_WHEN( "Seconds to hertz using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::hertz> hertzConverter;
			auto y = hertzConverter(.25, Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(4.0));
		}
		AND_WHEN( "Seconds to bpm using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::bpm> bpmConverter;
			auto y = bpmConverter(0.5, Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(120.0));
		}
		AND_WHEN( "Seconds to milliseconds using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::milliseconds> msConverter;
			auto y = msConverter(1.2345, Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(1234.5));
		}
		Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::midinote> midinoteConverter;
		AND_WHEN( "Seconds to mininote 57 using enum unit" ) {
			auto y = midinoteConverter(1/220., Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(57.0));
		}
		AND_WHEN( "Seconds to mininote 69 using enum unit" ) {
			auto y = midinoteConverter(1/440., Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(69.0));
		}
		Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::cents> centsConverter;
		AND_WHEN( "Seconds to 5700 cents using enum unit" ) {
			auto y = centsConverter(1/220., Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(5700.0));
		}
		AND_WHEN( "Seconds to 6900 cents using enum unit" ) {
			auto y = centsConverter(1/440., Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(6900.0));
		}
		AND_WHEN( "Seconds to bark using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::bark> barkConverter;
			auto y = barkConverter(0.001785990780318596, Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(5.0));
		}
		AND_WHEN( "Seconds to mel using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::mel> melConverter;
			auto y = melConverter(0.001, Dataspace::TimeUnit::seconds);
			REQUIRE( y == Approx(999.9855371396243));
		}
	}
	
	GIVEN( "Conversion is between non-neutral units" ) {
		
		Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::midinote> midinoteConverter;
		WHEN( "0.5 speed to mininote" ) {
			auto y = midinoteConverter(0.5, Dataspace::TimeUnit::playbackspeed);
			REQUIRE( y == Approx(-12.0) );
		}
		WHEN( "1.0 speed to mininote" ) {
			auto y = midinoteConverter(1.0, Dataspace::TimeUnit::playbackspeed);
			REQUIRE( y == Approx(0.0) );
		}
		WHEN( "2.0 speed to mininote" ) {
			auto y = midinoteConverter(2.0, Dataspace::TimeUnit::playbackspeed);
			REQUIRE( y == Approx(12.0) );
		}
		
		Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::playbackspeed> playbackspeedConverter;
		AND_WHEN( "midinote -12 to speed using enum unit" ) {
			auto y = playbackspeedConverter(-12.0, Dataspace::TimeUnit::midinote);
			REQUIRE( y == Approx(0.5));
		}
		AND_WHEN( "midinote 0 to speed using enum unit" ) {
			auto y = playbackspeedConverter(0.0, Dataspace::TimeUnit::midinote);
			REQUIRE( y == Approx(1.0));
		}
		AND_WHEN( "midinote -12 to speed using enum unit" ) {
			auto y = playbackspeedConverter(12, Dataspace::TimeUnit::midinote);
			REQUIRE( y == Approx(2.0));
		}
		
		AND_WHEN( "Hertz to mel scale using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::mel> melConverter;
			auto y = melConverter(1000.0, Dataspace::TimeUnit::hertz);
			REQUIRE( y == Approx(999.9855371396243));
		}
		AND_WHEN( "Mel scale to Hertz using enum unit" ) {
			Jamoma::Dataspace::Time<double, Dataspace::TimeUnit::hertz> hertzConverter;
			auto y = hertzConverter(999.9855371396243, Dataspace::TimeUnit::mel);
			REQUIRE( y == Approx(1000.0));
		}
	}
}
