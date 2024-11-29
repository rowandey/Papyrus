#include <iostream>
#include <chrono>
#include <thread>

class MillisecondClock {
public:
    // Start the clock by recording the current time
    void start() {
        initialStart = std::chrono::high_resolution_clock::now();
        currentStart = std::chrono::high_resolution_clock::now();
    }

    // Get the elapsed time in milliseconds since the clock was started
    long long perSecondCheck() {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - currentStart);
        return duration.count();
    }

    // Get the elapsed time in milliseconds since the clock was started
    long long elapsedMilliseconds() {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - initialStart);
        return duration.count();
    }

    void resetClock() {
        currentStart = std::chrono::high_resolution_clock::now();
    }

private:
    std::chrono::high_resolution_clock::time_point initialStart; // Store the start time
    std::chrono::high_resolution_clock::time_point currentStart;
};