#include "threadWorks.hpp"

// Static member initialization
std::atomic<bool> threadWorks::isProgramActive(true);
std::mutex threadWorks::consoleMutex;
std::atomic<int> threadWorks::totalPayloadsSent(0);
std::atomic<int> threadWorks::totalPayloadsSuccessful(0);
std::atomic<float> threadWorks::packetsPerSecond(0);

// Static signal handler function
void threadWorks::signalHandler(int signal) {
    std::lock_guard<std::mutex> guard(consoleMutex);
    std::cout << "\nStopping program..." << std::endl;
    isProgramActive = false;
}

void threadWorks::sendRequest(apiClient& client, bool verbose, matchBuilder& randMatch, std::string payload, MillisecondClock& clock) {
    std::transform(payload.begin(), payload.end(), payload.begin(), ::tolower);
    std::string response;

    // If the payload is empty it will send a normal get request
    // If the payload is lol it will send a randomized match
    // If the payload is ocean it will send a randomized ocean payload
    // If its any non empty value that isnt these 2 it will follow the file path
    if (payload.empty()) {
        response = client.sendGETRequest();
    } else if (payload == "lol") {
        matchBuilder randMatch;
        client.setPayload(randMatch.randomMatch().dump(4));
        response = client.sendPOSTRequest();
    } else if (payload == "ocean") {
        oceanBuilder myOcean;
        client.setPayload(myOcean.randomOcean());
        response = client.sendPOSTRequest();
    } else {
        std::ifstream f(payload);
        json jsonPayload = json::parse(f); 
        client.setPayload(jsonPayload);
        response = client.sendPOSTRequest();
    }


    if (verbose) {
        std::cout << "Response: " << response << std::endl;
    } else {
        totalPayloadsSent++;

        // Mutex guarded packets per second calculations
        std::lock_guard<std::mutex> guard(consoleMutex);
        // Prevent division by zero
        long long elapsedSec = clock.elapsedMilliseconds() / 1000;
        if (elapsedSec > 0) {
            packetsPerSecond = totalPayloadsSent / static_cast<float>(elapsedSec);
        } else {
            packetsPerSecond = 0; // Default value if elapsed time is too short
        }

        if (response == "200") {
            totalPayloadsSuccessful++;
        }

        // Print updated info on the same line
        std::cout << "\rTotal Sent: " << totalPayloadsSent
                  << " | Successful: " << totalPayloadsSuccessful
                  << " | Failed: " << (totalPayloadsSent - totalPayloadsSuccessful)
                  << " | Packets/s: " << packetsPerSecond
                  << " | Elapsed Time: " << clock.elapsedMilliseconds()
                  << std::flush;  // Ensure everything is written immediately to avoid any delay
    }
}

// Orchestrates the sending of requests and main loop for program
void threadWorks::runWorkerThread(const std::string& targetURL, const std::string& endpoint, bool verbose, int payloadCount, int rateLimit, int ramp, int spike, std::string payload, std::string parameter) {
    MillisecondClock clock;
    matchBuilder randMatch;
    apiClient client(targetURL);
    client.setEndpoint(endpoint);
    client.setParameter(parameter);

    clock.start();
    while (isProgramActive) {
        sendRequest(client, verbose, randMatch, payload, clock);

        if (payloadCount > 0 && --payloadCount == 0) break;

        if (rateLimit) {
            std::this_thread::sleep_for(std::chrono::milliseconds(rateLimit));
        }
        if (ramp > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ramp));
            ramp = std::max(ramp / 2, 1);
        } else if (spike > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(myRandom::generateRandomInt(0, spike)));
        }
    }
}
