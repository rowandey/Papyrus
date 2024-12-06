#pragma once

#include <iostream>
#include <atomic>
#include <mutex>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include "matchBuilder.hpp"
#include "utilities.hpp"
#include "apiClient.hpp"
#include "payloadBuilder.hpp"
#include <csignal>

class threadWorks {
public:
    static std::atomic<bool> isProgramActive;            // Shared across threads and signal handler
    static std::mutex consoleMutex;                      // Used in the signal handler
    static std::atomic<int> totalPayloadsSent;           // Shared across threads
    static std::atomic<int> totalPayloadsSuccessful;     // Shared across threads
    static std::atomic<int> pastSecondPackets;           // Shared across threads
    static std::atomic<int> pastSecondHighest;           // Shared across threads

    // Signal handler to stop the program
    static void signalHandler(int signal);

    // Function to send requests and optionally log verbose output
    static void sendRequest(ApiClient& client, bool verbose, matchBuilder& randMatch, std::string payload, std::string requestType, MillisecondClock& clock);

    // Worker thread function that sends requests based on the provided parameters
    static void runWorkerThread(const std::string& targetURL, const std::string& endpoint, bool verbose, int payloadCount, int rateLimit, int ramp, int spike, std::string payload, std::string requestType, std::string parameter);
};
