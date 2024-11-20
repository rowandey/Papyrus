#include <iostream>
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
#include "../include/apiClient.hpp"
#include <csignal>
#include <chrono>
#include <thread>
#include <vector>

using json = nlohmann::json;

bool isProgramActive = true;

// Signal handler to gracefully stop the loop
void signalHandler(int signal) {
    std::cout << "Stopping program..." << std::endl;
    isProgramActive = false;
}

// Function that runs the logic in a single thread
void runWorkerThread() {
    // Declares the randMatch class so that we can build random games
    matchBuilder randMatch;

    // Defines the target server and API endpoint that we are going to blast
    ApiClient client("http://10.0.0.11:80");
    client.setEndpoint("/addMatch");

    // Main loop that sends new requests
    while (isProgramActive) {
        // Builds and sends the payload containing the newly built random match
        client.setPayload(randMatch.randomMatch().dump(4));
        client.sendRequest();
    }
}

int main() {
    // Attach the signal handler to interrupt signals
    std::signal(SIGINT, signalHandler);
    std::cout << "Program is running. Press Ctrl+C to stop." << std::endl;

    // Number of threads to run
    const int numThreads = 16; // Adjust this to set the number of concurrent threads
    std::vector<std::thread> threads;

    // Launch multiple threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(runWorkerThread);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << "Program has stopped." << std::endl;
    return 0;
}