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
		Dataspace::Angle<double, Dataspace::AngleUnit::radian>		radianConverter;

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
		Dataspace::Angle<double, Dataspace::AngleUnit::degree>		degreeConverter;
		
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
		Jamoma::Dataspace::Distance<double, Dataspace::DistanceUnit::meters>	metersConverter;
		
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




#ifdef USE_OLD_UNIT_TESTS
		
		void testGain()
		{
			// Dataspace Test
			double y = 0;
			
			
			// Gain: conversions to linear
			Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::linear>		linearGainConverter;
			
			y = linearGainConverter(0.5);
			mTest->TEST_ASSERT("unspecified unit is assumed to be the native unit (linear)", mTest->compare(y, 0.5));
			
			y = linearGainConverter(-6, Dataspace::GainUnit::db);
			mTest->TEST_ASSERT("db unit specified as enum", mTest->compare(y, 0.50118723362727224));
			
			y = linearGainConverter(-12, "db");
			// TODO: test
			mTest->TEST_ASSERT("db unit specified as string", mTest->compare(y, 0.25118864315095796));
			
			
			// Gain: conversions to db
			Jamoma::Dataspace::Gain<double, Dataspace::GainUnit::db>		dbGainConverter;
			
			y = dbGainConverter(0.5);
			mTest->TEST_ASSERT("unspecified unit is assumed to be the native unit (db)", mTest->compare(y, 0.5));
			
			y = dbGainConverter(2.0, Dataspace::GainUnit::linear);
			mTest->TEST_ASSERT("linear-to-db", mTest->compare(y, 6.0205999132796242));
			
			y = dbGainConverter(100.0, Dataspace::GainUnit::midi);
			mTest->TEST_ASSERT("midi-to-db using enum unit", mTest->compare(y, 0.0));
			
			y = dbGainConverter(50, "midi");
			mTest->TEST_ASSERT("midi-to-db using string unit", mTest->compare(y, -28.999923402717513));
			
		}
		
		
		void testNone()
		{
			;
		}
		
		
		void testSpeed()
		{
			double y = 0;
			
			// Distance: conversion to meters
			Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::meterPerSecond>	meterPerSecondConverter;
			
			y = meterPerSecondConverter(0.5);
			mTest->TEST_ASSERT("unspecified unit is assumed to be the native unit (m/s)", mTest->compare(y, 0.5));
			
			
			// *** To neutral unit ***
			y = meterPerSecondConverter(36.0, Dataspace::SpeedUnit::kilometerPerHour);
			mTest->TEST_ASSERT("km/h to m/s using enum unit", mTest->compare(y, 10.0));
			
			y = meterPerSecondConverter(36.0, Dataspace::SpeedUnit::kmph);
			mTest->TEST_ASSERT("kmph to m/s using enum unit", mTest->compare(y, 10.0));
			
			y = meterPerSecondConverter(50.0, Dataspace::SpeedUnit::milesPerHour);
			mTest->TEST_ASSERT("mi/h to m/s using enum unit", mTest->compare(y, 22.35200));
			
			/* TODO : Commented out due to shortcoming with our current unit test comapre method
			y = meterPerSecondConverter(45.0, Dataspace::SpeedUnit::knot);
			mTest->TEST_ASSERT("knot to m/s using enum unit", mTest->compare(y, 23.15));
			 */
			
			y = meterPerSecondConverter(20.0, Dataspace::SpeedUnit::footPerSecond);
			mTest->TEST_ASSERT("ft/s to m/s using enum unit", mTest->compare(y, 6.09600));
			
			
			// *** From neutral unit ***
			Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::kilometerPerHour>	kilometerPerHourConverter;
			y = kilometerPerHourConverter(10.0, Dataspace::SpeedUnit::meterPerSecond);
			mTest->TEST_ASSERT("m/s to km/h using enum unit", mTest->compare(y, 36.0));
			
			Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::kmph>				kmphConverter;
			y = kmphConverter(10.0, Dataspace::SpeedUnit::meterPerSecond);
			mTest->TEST_ASSERT("m/s to kmph using enum unit", mTest->compare(y, 36.0));
			
			/* TODO : Commented out due to shortcoming with our current unit test comapre method
			Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::milesPerHour>		milesPerHourConverter;
			y = milesPerHourConverter(22.35200, Dataspace::SpeedUnit::meterPerSecond);
			mTest->TEST_ASSERT("m/s to mi/h using enum unit", mTest->compare(y, 50.0));
			
			Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::knot>				knotConverter;
			y = knotConverter(23.15, Dataspace::SpeedUnit::meterPerSecond);
			mTest->TEST_ASSERT("m/s to knot using enum unit", mTest->compare(y, 45.0));
			
			Jamoma::Dataspace::Speed<double, Dataspace::SpeedUnit::footPerSecond>	footPerSecondConverter;
			y = footPerSecondConverter(6.09600, Dataspace::SpeedUnit::meterPerSecond);
			mTest->TEST_ASSERT("m/s to ft/s using enum unit", mTest->compare(y, 20.0));
			 */

		}
		
		void testTemperature()
		{
			double y = 0;
			
			// Distance: conversion to meters
			Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::kelvin>	kelvinConverter;
			
			y = kelvinConverter(0.5);
			mTest->TEST_ASSERT("unspecified unit is assumed to be the native unit (Kelvin)", mTest->compare(y, 0.5));
			
			
			// *** To neutral unit ***
			y = kelvinConverter(123.4, Dataspace::TemperatureUnit::k);
			mTest->TEST_ASSERT("K to Kelvin using enum unit", mTest->compare(y, 123.4));
			
			y = kelvinConverter(0.0, Dataspace::TemperatureUnit::celsius);
			mTest->TEST_ASSERT("Celsius to Kelvin using enum unit", mTest->compare(y, 273.15));
			
			y = kelvinConverter(0.0, Dataspace::TemperatureUnit::c);
			mTest->TEST_ASSERT("C to Kelvin using enum unit", mTest->compare(y, 273.15));
			
			y = kelvinConverter(32.0, Dataspace::TemperatureUnit::fahrenheit);
			mTest->TEST_ASSERT("Fahrenheit to Kelvin using enum unit", mTest->compare(y, 273.15));
			
			y = kelvinConverter(32.0, Dataspace::TemperatureUnit::f);
			mTest->TEST_ASSERT("F to Kelvin using enum unit", mTest->compare(y, 273.15));
			
			
			// *** From neutral unit ***
			Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::k>	kConverter;
			y = kConverter(123.4, Dataspace::TemperatureUnit::kelvin);
			mTest->TEST_ASSERT("Kelvin to K using enum unit", mTest->compare(y, 123.4));
			
			Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::celsius>	celsiusConverter;
			y = celsiusConverter(273.15, Dataspace::TemperatureUnit::kelvin);
			mTest->TEST_ASSERT("Kelvin to Celsius using enum unit", mTest->compare(y, 0.0));
			
			Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::celsius>	cConverter;
			y = cConverter(273.15, Dataspace::TemperatureUnit::kelvin);
			mTest->TEST_ASSERT("Kelvin to C using enum unit", mTest->compare(y, 0.0));
			
			/* TODO: The following two tests fails in spite ofe the numbers being very close.
			 This is a problem with the unit test mechanism rather than the dataspace conversions,
			 and for the time being the two tests are commented out.
			 
			 The question is whether compare() is able to do the job that it's meant to?
			 SEE: https://github.com/jamoma/jamoma2/issues/99
			 */
			
			/*
			Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::fahrenheit>	fahrenheitConverter;
			y = fahrenheitConverter(273.15, Dataspace::TemperatureUnit::kelvin);
			mTest->TEST_ASSERT("Kelvin to Fahrenheit using enum unit", mTest->compare(y, 32.0, 1000));
			
			Jamoma::Dataspace::Temperature<double, Dataspace::TemperatureUnit::fahrenheit>	fConverter;
			y = fConverter(273.15, Dataspace::TemperatureUnit::kelvin);
			mTest->TEST_ASSERT("Kelvin to F using enum unit", mTest->compare(y, 32.0, 2));
			 */
		}
		
		
	};

#endif // #ifdef USE_OLD_UNIT_TESTS

