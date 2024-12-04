#include <iostream>
#include "matchBuilder.hpp"
#include "clock.hpp"
#include "apiClient.hpp"
#include "commandLine.hpp"
#include "payloadBuilder.hpp"
#include <csignal>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

class threadWorks {
public:
    static std::atomic<bool> isProgramActive; // Static to share across threads and signal handler
    static std::mutex consoleMutex;          // Static to be accessible in the static signal handler
    static std::atomic<int> totalPayloadsSent; // Static to be shared across threads
    static std::atomic<int> totalPayloadsSuccessful; // Static to be shared across threads
    static std::atomic<int> pastSecondPackets; // Static to be shared across threads
    static std::atomic<int> pastSecondHighest; // Static to be shared across threads

    // Static signal handler
    static void signalHandler(int signal) {
        std::lock_guard<std::mutex> guard(consoleMutex);
        std::cout << "\nStopping program..." << std::endl;
        isProgramActive = false;
    }

    // Static function to send a request and optionally log verbose output
    static void sendRequest(ApiClient& client, bool verbose, matchBuilder& randMatch, std::string payload, std::string requestType, MillisecondClock& clock) {
        std::string response;

        if (payload.empty()) {
            matchBuilder randMatch;
            client.setPayload(randMatch.randomMatch().dump(4));
        } else {
            client.setPayload(payload);
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
            std::cout << "\r" << std::string(100, ' ') << "\r";
            std::cout << "\rTotal Sent: " << totalPayloadsSent
                      << " | Successful: " << totalPayloadsSuccessful
                      << " | Failed: " << (totalPayloadsSent - totalPayloadsSuccessful)
                      << " | Packets/s: " << pastSecondHighest
                      << " | Elapsed Time: " << clock.elapsedMilliseconds()
                      << std::flush;
        }
    }

    // Static worker function
    static void runWorkerThread(const std::string& targetURL, const std::string& endpoint, bool verbose, int payloadCount, int rateLimit, int ramp, int spike, std::string payload, std::string requestType, std::string parameter) {
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
};