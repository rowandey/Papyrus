#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>
#include <climits>
#include <random>


class MillisecondClock {
public:
    // Start the clock by recording the current time
    void start();

    // Get the elapsed time in milliseconds since the clock was started
    long long perSecondCheck();

    // Get the elapsed time in milliseconds since the clock was started
    long long elapsedMilliseconds();

    // Reset the clock to the current time
    void resetClock();

private:
    std::chrono::high_resolution_clock::time_point initialStart; // Store the start time
    std::chrono::high_resolution_clock::time_point currentStart;
};



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


class myRandom {
public:
    // Generates a random integer between min and max (inclusive)
    static int generateRandomInt(int min, int max);

    // Generates a random string of a specified length containing letters and digits
    static std::string generateRandomString(size_t length);

    // Generates a random numeric string of a specified length
    static std::string generateRandomNumberString(size_t length);

    // Generates a random boolean (true or false)
    static bool getRandomBool();
};
