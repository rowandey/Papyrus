#include "millisecondClock.hpp"

#include <chrono>

// Start the clock by recording the current time
void MillisecondClock::start() {
    initialStart = std::chrono::high_resolution_clock::now();
    currentStart = std::chrono::high_resolution_clock::now();
}

// Get the elapsed time in milliseconds since the clock was started
long long MillisecondClock::perSecondCheck() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - currentStart);
    return duration.count();
}

// Get the elapsed time in milliseconds since the clock was started
long long MillisecondClock::elapsedMilliseconds() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - initialStart);
    return duration.count();
}

// Reset the clock to start counting from the current time
// Used in calculating packets per second
void MillisecondClock::resetClock() {
    currentStart = std::chrono::high_resolution_clock::now();
}
