#include <string>
#include <iostream>
#include "../../src/cliHelper.hpp"

class TEST_cliHelper {
    public:
    static void testParseIntArgValid() {
        std::cout << "\nTesting a valid input for parseIntArg" << std::endl;
        std::cout << "\nExpecting: 1" << std::endl;

        const char* input = "1";

        try {
            int result = cliHelper::parseIntArg(input, "threads");
            std::cout << "\nGot: " << result << std::endl;
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "\nGot: ERROR" << std::endl;
            std::cout << "\033[31m==========FAILED==========\033[0m" << std::endl;
        }
    }

    static void testParseIntArgInvalid() {
        std::cout << "\nTesting a valid input for parseIntArg" << std::endl;

        const char* input = "abcdefg";
        
        try {
            int result = cliHelper::parseIntArg(input, "threads");
            std::cout << "\nGot: " << result << std::endl;
            std::cout << "\033[31m==========FAILED==========\033[0m" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        }
    }

    static void testParseIntArgOutOfBounds() {
        std::cout << "\nTesting a valid input for parseIntArg" << std::endl;

        const char* input = "999999999999999999999999999999";
        
        try {
            int result = cliHelper::parseIntArg(input, "threads");
            std::cout << "\nGot: " << result << std::endl;
            std::cout << "\033[31m==========FAILED==========\033[0m" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "\033[32m==========PASSED==========\033[0m" << std::endl;
        }
    }
};

int main () {
    std::cout << "TEST START\n" << std::endl;

    TEST_cliHelper::testParseIntArgValid();
    TEST_cliHelper::testParseIntArgInvalid();
    TEST_cliHelper::testParseIntArgOutOfBounds();

    std::cout << "\n\nTEST END\n" << std::endl;
}