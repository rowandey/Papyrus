#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include <climits>

class cliHelper {
public:
    // Helper function to validate and parse integer arguments
    static int parseIntArg(const char* arg, const std::string& flagName);

    // Function to display program info (banner)
    static void printBanner();

    // Helper function for parsing command-line arguments
    static void parseArguments(int argc, char* argv[], int& numThreads, int& payloadCount, int& rateLimit, 
                                int& ramp, int& spike, std::string& target, std::string& endpoint, 
                                bool& verbose, std::string& payload, 
                                std::string& parameter);

    // Function to display help message
    static void displayHelp();

    // Helper function to check if a number is a valid integer or not and returns 1 if it is
    static bool isValidInt(double num);

private:
    // No private members, just static helper functions
};
