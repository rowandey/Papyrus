#include <string>
#include <iostream>
#include "../../src/cliHelper.hpp"

class TEST_cliHelper {
    public:
    static void testParseIntArgValid() {
        std::cout << "\nTesting a valid input for parseIntArg" << std::endl;
        std::cout << "Expecting: 1" << std::endl;

        const char* input = "1";

        try {
            int result = cliHelper::parseIntArg(input, "threads");
            std::cout << "Got: " << result << std::endl;
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Got: ERROR" << std::endl;
            std::cout << "\033[31m==========FAILED==========\033[0m" << std::endl;
        }
    }

    static void testParseIntArgInvalid() {
        std::cout << "\nTesting an invalid input for parseIntArg" << std::endl;

        const char* input = "abcdefg";
        
        try {
            int result = cliHelper::parseIntArg(input, "threads");
            std::cout << "Got: " << result << std::endl;
            std::cout << "\033[31m==========FAILED==========\033[0m" << std::endl;
        } catch (const std::exception& e) {
			std::cout << "Got: " << e.what() << std::endl;
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        }
    }

    static void testParseIntArgOutOfBounds() {
        std::cout << "\nTesting a out of bounds input for parseIntArg" << std::endl;

        const char* input = "999999999999999999999999999999";
        
        try {
            int result = cliHelper::parseIntArg(input, "threads");
            std::cout << "Got: " << result << std::endl;
            std::cout << "\033[31m==========FAILED==========\033[0m" << std::endl;
        } catch (const std::exception& e) {
			std::cout << "Got: " << e.what() << std::endl;
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        }
    }

    static void testParseArgumentsValid() {
        std::cout << "\nTesting a valid set of arguments" << std::endl;
        int argc = 20;
        char* argv[] = {
            (char*)"program",                 // Program name, arg 0
            (char*)"--threads",               // arg 1
            (char*)"4",                       // arg 2
            (char*)"--target",                // arg 3
            (char*)"https://www.example.com", // arg 4
            (char*)"--endpoint",              // arg 5
            (char*)"/test",                   // arg 6
            (char*)"--parameter",             // arg 7
            (char*)"id=1&name=test",          // arg 8
            (char*)"--count",                 // arg 9
            (char*)"100",                     // arg 10
            (char*)"--rate",                  // arg 11
            (char*)"500",                     // arg 12 (milliseconds)
            (char*)"--verbose",               // arg 13 (flag, no value)
            (char*)"--spike",                 // arg 14
            (char*)"300",                     // arg 15 (milliseconds)
            (char*)"--ramp",                  // arg 16
            (char*)"100",                     // arg 17 (milliseconds)
            (char*)"--payload",               // arg 18
            (char*)"payload.json",            // arg 19
            nullptr                           // End of arguments
        };
        int numThreads = 1, payloadCount = 0, rateLimit = 0, ramp = 0, spike = 0;
        bool verbose = false;
        std::string target;
        std::string endpoint;
        std::string payload;
        std::string parameter;

        cliHelper::parseArguments(argc, argv, numThreads, payloadCount, rateLimit, ramp, spike, target, endpoint, verbose, payload, parameter);

        if (numThreads == 4 && payloadCount == 100 && rateLimit == 500 && ramp == 100 && spike == 300 && 
            target == "https://www.example.com" && endpoint == "/test" && verbose == true && 
            payload == "payload.json" && parameter == "id=1&name=test") 
        {
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        }
        else {
            std::cout << "\033[32m==========FAILED==========\033[0m" << std::endl;
        }
    }

	// no more tests for the main parser due to the tests requiring a fork of the process, which seems excessive.
};

int main () {
    std::cout << "TEST START\n" << std::endl;

    // int conversion/parsing
    TEST_cliHelper::testParseIntArgValid();
    TEST_cliHelper::testParseIntArgInvalid();
    TEST_cliHelper::testParseIntArgOutOfBounds();

    // cli parser
    TEST_cliHelper::testParseArgumentsValid();

    std::cout << "\n\nTEST END\n" << std::endl;
}