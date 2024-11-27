#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class cliHelper{
    public:
    // Helper function to validate and parse integer arguments
    static int parseIntArg(const char* arg, const std::string& flagName) {
        try {
            return std::stoi(arg);
        } catch (const std::invalid_argument&) {
            throw std::runtime_error("Error: Invalid number for " + flagName + ". Must be a positive integer.");
        } catch (const std::out_of_range&) {
            throw std::runtime_error("Error: Number out of range for " + flagName + ".");
        }
    }

    // TODO: Add the new flags created like --spike --ramp and all the others
    // Function to display help message
    static void displayHelp() {
        std::cout << "Usage: ./program [options] {value}\n"
                << "Options:\n"
                << "  -h, --help                Show this help message\n"
                << "  -th, --threads [num]      Number of threads to run (default: 1)\n"
                << "  -ta, --target [url]       Target URL ex. \"http://mtrack.com\"\n"
                << "  -t, --type [GET|POST]     Specify GET to send GET request or POST to send payloads\n"
                << "  -c, --count [num]         Number of payloads to send\n"
                << "  -r, --rate [ms]           Rate limit in milliseconds between sent payloads\n"
                << "  -e, --endpoint [path]     API endpoint ex. \"/addMatch\"\n"
                << "  -v, --verbose             Enable verbose output\n"
                << "  -s, --spike [ms]          Each thread will send data in random spikes \n"
                << "  -ra, --ramp [ms]           Each thread will send data gradually faster\n"
                << "  -p, --payload [filepath]  Option to specify file path to .JSON payload \n";
    }

    // Helper function to check if a number is a valid integer or not and returns
    // 1 if it is
    static bool isValidInt(double num) {
        return std::floor(num) == num && num >= INT_MIN && num <= INT_MAX;
    }

};