#include <iostream>
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
#include "../include/apiClient.hpp"
#include <csignal>
#include <chrono>
#include <thread>

using json = nlohmann::json;

bool isProgramActive = true;

// Signal handler to gracefully stop the loop
void signalHandler(int signal) {
    std::cout << "Stopping program..." << std::endl;
    isProgramActive = false;
}

int main() {

    // Attach the signal handler to interrupt signals
    std::signal(SIGINT, signalHandler);
    std::cout << "Program is running. Press Ctrl+C to stop." << std::endl;

    // Declares the randMatch class so that we can build random games 
    matchBuilder randMatch;

    // Defines the target server and api endpoint that we are gonna blast
    ApiClient client("http://10.0.0.11:80");
    client.setEndpoint("/addMatch");

    // Main loop that sends new requests 
    std::cout << "Program is active..." << std::endl;
    while (isProgramActive) {

        // Builds and sends the payload containing the newly built random match
        client.setPayload(randMatch.randomMatch().dump(4));
        client.sendRequest();

        // Simulate some delay between the requests
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Program has stopped." << std::endl;

    return 0;
}


