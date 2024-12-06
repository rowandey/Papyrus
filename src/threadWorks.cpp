#include "threadWorks.hpp"

// Static member initialization
std::atomic<bool> threadWorks::isProgramActive(true);
std::mutex threadWorks::consoleMutex;
std::atomic<int> threadWorks::totalPayloadsSent(0);
std::atomic<int> threadWorks::totalPayloadsSuccessful(0);
std::atomic<int> threadWorks::pastSecondPackets(0);
std::atomic<int> threadWorks::pastSecondHighest(0);

// Static signal handler function
void threadWorks::signalHandler(int signal) {
    std::lock_guard<std::mutex> guard(consoleMutex);
    std::cout << "\nStopping program..." << std::endl;
    isProgramActive = false;
}

void threadWorks::sendRequest(ApiClient& client, bool verbose, matchBuilder& randMatch, std::string payload, std::string requestType, MillisecondClock& clock) {
    std::string response;

    if (payload.empty()) {
        matchBuilder randMatch;
        client.setPayload(randMatch.randomMatch().dump(4));
    } else {
        // std::ifstream f(payload);
        // json jsonPayload = json::parse(f);
        //std::cout << "Not using: " << payload << " at the moment." << std::endl; 
        oceanBuilder myOcean;
        client.setPayload(myOcean.randomOcean().dump(4));
    }

    if (requestType == "GET" || requestType == "get") {
        response = client.sendGETRequest();
    } else {
        response = client.sendPOSTRequest();
    }

    std::lock_guard<std::mutex> guard(consoleMutex);
    if (clock.perSecondCheck() >= 1000) {
        clock.resetClock();

        if (pastSecondHighest < pastSecondPackets) {
            pastSecondHighest.store(pastSecondPackets.load(), std::memory_order_relaxed);
        }
        pastSecondPackets = 0;
    }

    if (verbose) {
        std::cout << "Response: " << response << std::endl;
    } else {
        totalPayloadsSent++;
        pastSecondPackets++;
        if (response == "200") {
            totalPayloadsSuccessful++;
        }

        // Move to the beginning of the line and clear it using a carriage return
        // TODO: Confirm that there is no output buffer problem.
        //std::cout << "\r" << std::string(100, ' ') << "\r";  // Clear the line with spaces

        // Print updated info on the same line
        std::cout << "\rTotal Sent: " << totalPayloadsSent
                  << " | Successful: " << totalPayloadsSuccessful
                  << " | Failed: " << (totalPayloadsSent - totalPayloadsSuccessful)
                  << " | Packets/s: " << pastSecondHighest
                  << " | Elapsed Time: " << clock.elapsedMilliseconds()
                  << std::flush;  // Ensure everything is written immediately to avoid any delay
    }
}



// Static worker function
void threadWorks::runWorkerThread(const std::string& targetURL, const std::string& endpoint, bool verbose, int payloadCount, int rateLimit, int ramp, int spike, std::string payload, std::string requestType, std::string parameter) {
    MillisecondClock clock;
    matchBuilder randMatch;
    ApiClient client(targetURL);
    client.setEndpoint(endpoint);
    client.setParameter(parameter);

    clock.start();
    while (isProgramActive) {
        sendRequest(client, verbose, randMatch, payload, requestType, clock);

        if (payloadCount > 0 && --payloadCount == 0) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(rateLimit));

        if (ramp > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(ramp));
            ramp = std::max(ramp / 2, 1);
        } else if (spike > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(myRandom::generateRandomInt(0, spike)));
        }
    }
}
