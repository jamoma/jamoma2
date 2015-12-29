/** @file
	@ingroup 	jamoma2
 
	@brief 		Unit test for Generator classes
 
	@author		Nathan Wolek
	@copyright	Copyright (c) 2005-2015 The Jamoma Group, http://jamoma.org.
	@license	This project is released under the terms of the MIT License.

 */

#include "Jamoma.h"


class GeneratorTest {
	
	Jamoma::UnitTest<GeneratorTest>*	mTest;
	
public:
	GeneratorTest(Jamoma::UnitTest<GeneratorTest>* test)
	: mTest(test)
	{
        testGenerateFunctions();
	}
    
    void testGenerateFunctions() {
        
        Jamoma::SampleBundle	test_sample_bundle(4, 128);
        
        test_sample_bundle.generate();
        
        for(int i = 0; i < test_sample_bundle[0].size(); i++) {
            for(int j = 0; j < test_sample_bundle.channelCount(); j++) {
                std::cout << "sample " << i << " in channel " << j << " = " << test_sample_bundle[j][i] << std::endl;
            }
        }
        
        
        test_sample_bundle.generate<Jamoma::Generator::Triangle<Jamoma::Sample>>();
        for (auto i=0; i < test_sample_bundle[0].size(); ++i) {
            for (auto j=0; j < test_sample_bundle.channelCount(); ++j)
                std::cout << "tri sample " << i << " in channel " << j << " = " << test_sample_bundle[j][i] << std::endl;
        }
        
    }

	
};

int main(int argc, const char * argv[])
{
	Jamoma::UnitTest<GeneratorTest>	aUnitTestInstance;
	return aUnitTestInstance.failureCount();
}
