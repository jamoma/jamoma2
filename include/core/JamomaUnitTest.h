/** @file
	
	@ingroup 	jamoma2
	
	@brief 		Define a parameter of a JamomaObject
 
	@author		Timothy Place
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#pragma once

#include "JamomaObject.h"
#include "third-party/gtest/gtest-internal.h"

namespace Jamoma {

	
	template <class T>
	class UnitTest {
		std::unique_ptr<T>	mUnitTest;
		int					mAssertionCount;
		int					mFailedAssertions;
		
	public:
		/**	Create an instance of your unit test.
			Your unit test will be passed a pointer to this wrapper instance, which you then use to log results.
		 */
		UnitTest()
		{
			mAssertionCount = 0;
			mFailedAssertions = 0;
			mUnitTest = std::make_unique<T>(this);
		}
		
		
		UnitTest(const UnitTest&) = delete;
		UnitTest(const UnitTest&&) = delete;

		
		/**	Destructor cleans up and logs the results of the test.
		 */
		~UnitTest()
		{
			log("\n");
			log("Number of assertions: %ld", mAssertionCount);
			log("Number of failed assertions: %ld", mFailedAssertions);
			log("\n");
		}
		
		
		/**	Log the outcome of a proceedure that should result as true.
			Test assertions are not like normal C++ assertions -- test assertions are not designed to crash when they fail.
			You probably don't want to call this directly -- it is much more convenient to use the #TEST_ASSERT macro instead.
		 
			@param aTestName			A name you wish to give the assertion.  Should be as descriptive as possible.
			@param aTestResult			You should pass 'true' if the assertion passes, or 'false' if it failed.
			@param filename				The filename where the assertion is located -- provided automatically if you use the #TEST_ASSERT macro instead.
			@param linenumber			The line number in source code of the assertion -- provided automatically if you use the #TEST_ASSERT macro instead.
			@return						Returns true if a == b, otherwise returns false.	
		 */
		void assertion(String aTestName, bool aTestResult, const char* filename, int linenumber)
		{
			++mAssertionCount;
			result(aTestName, aTestResult, filename, linenumber);
			if (!aTestResult)
				++mFailedAssertions;
		}
		
		
		/**	Declare a result to be expected.
		 A failed expectation will be flagged as an error in the IDE (Xcode or VS).
		 
		 @param		aTestName	The name of the expectation for logging purposes.
		 @param		aTestName	The result received.
		 @return				Returns a 1 if the expection failed, 0 if it passes.
		 */
		#define TEST_ASSERT(aTestName, aTestResult) \
				assertion((aTestName),(aTestResult), __FILE__, __LINE__)


		/**	Post a message to the console.
			Adequate indenting is provided for free, as are newlines at the end.
			At some point we may additionally log these messages in other ways (e.g. to a database).
			@param	fmtstring	The string to post
			@param	...			Values to be substituted into the string
			TODO: Would be nice to have this as an output stream instead of this clunky old-sk00l C stuff
		 */
		void log(const char *fmtstring, ...)
		{
			char	str[4096];
			char	fullstr[4096];
			va_list	ap;
			
			va_start(ap, fmtstring);
			vsnprintf(str, 4000, fmtstring, ap);
			va_end(ap);
			str[4095] = 0;
			
			strncpy(fullstr, "		", 4095);
			strncat(fullstr, str, 4095);
			std::cerr << fullstr << std::endl;
		}


		/**	Determine if two floating-point numbers (32- or 64-bit) are equivalent in value, tolerant of floating-point precision.
			Internally using the FloatingPoint comparison developed by Google for GTest.
			@param	a			The first value to test
			@param	b			The second value to test
			@param	equivalent	The expected result when comparing the two floats a and b. Defaults to TRUE.
			@param	maxUlps		The maximum number of "units in last place" that can deviate and still evaluate as equivalent.
								See https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
			@return				Returns true if a is equivalent to b, otherwise returns false.
		 */
		template <class U>
		bool compare(U a, U b, bool equivalent = true, size_t maxUlps = 4)
		{
			testing::internal::FloatingPoint<U> aa(a);
			testing::internal::FloatingPoint<U> bb(b);
			
			bool result = aa.AlmostEquals(bb, maxUlps);
			
			if (result == equivalent) // Was this the expected result?
				return true;
			else
				return false;
		}

		
		auto failureCount()
		{
			return mFailedAssertions;
		}
		
	private:
		
		
		// Used internally for posting assertion info
		void result(String name, bool aResult, const char* filename = "", int linenumber = 0)
		{
			// Note: we don't post passing assertions because the log (at least in Xcode) starts suppressing the messages and failures won't be posted
			if (aResult == false) {
#ifdef JAMOMA_PLATFORM_WIN
				std::cout << filename << "(" << linenumber << ") : error: " << "Test Assertion Failed -- " << name << std::endl;
#else
				std::cout << filename << ":" << linenumber << ": error: " << "Test Assertion Failed -- " << name << std::endl;
#endif
			}
		}

		
	};
	
	
	
	
} // namespace Jamoma
