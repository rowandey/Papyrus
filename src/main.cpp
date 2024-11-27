#include <iostream>
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
#include "../include/apiClient.hpp"
#include "../include/commandLine.hpp"
#include "../include/payloadBuilder.hpp"
#include <csignal>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

using json = nlohmann::json;

std::atomic<int> totalPayloadsSent(0);
std::atomic<int> totalPayloadsSuccessful(0);
bool isProgramActive = true;
std::mutex consoleMutex;  // Mutex for synchronizing console output

// Signal handler to gracefully stop the loop
void signalHandler(int signal) {
    std::lock_guard<std::mutex> guard(consoleMutex);
    std::cout << "\nStopping program..." << std::endl;
    isProgramActive = false;
}

// Function to send a request and optionally log verbose output
void sendRequest(ApiClient& client, bool verbose, matchBuilder& randMatch, std::string payload, std::string requestType) {
    std::string response;

    if (payload.length() < 1) {
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
    if (verbose) {
        std::cout << "Response: " << response << std::endl;
    } else {
        totalPayloadsSent++;
        if (response == "200") {
            totalPayloadsSuccessful++;
        }
        std::cout << "\rPayloads sent: " << totalPayloadsSent
                  << " | Successful: " << totalPayloadsSuccessful
                  << " | Failed: " << (totalPayloadsSent - totalPayloadsSuccessful)
                  << std::flush;
    }
}

// Worker function
void runWorkerThread(const std::string& targetURL, const std::string& endpoint, bool verbose, int payloadCount, int rateLimit, int ramp, int spike, std::string payload, std::string requestType) {
    
    matchBuilder randMatch;
    ApiClient client(targetURL);
    client.setEndpoint(endpoint);

    while (isProgramActive) {
        sendRequest(client, verbose, randMatch, payload, requestType);

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

// Helper function for parsing command-line arguments
void parseArguments(int argc, char* argv[], int& numThreads, int& payloadCount, int& rateLimit, int& ramp, int& spike, std::string& target, std::string& endpoint, bool& verbose, std::string& payload, std::string& requestType) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        try {
            if (arg == "--help" || arg == "-h") {
                cliHelper::displayHelp();
                exit(0);
            } else if (arg == "--threads" || arg == "-th") {
                numThreads = cliHelper::parseIntArg(argv[++i], "threads");
            } else if (arg == "--target" || arg == "-ta") {
                target = argv[++i];
                if (target.empty()) throw std::runtime_error("Error: Target value cannot be empty.");
            } else if (arg == "--type" || arg == "-t") {
                requestType = argv[++i];
                if (target.empty()) throw std::runtime_error("Error: Target value cannot be empty.");
            } else if (arg == "--count" || arg == "-c") {
                payloadCount = cliHelper::parseIntArg(argv[++i], "count");
            } else if (arg == "--rate" || arg == "-r") {
                rateLimit = cliHelper::parseIntArg(argv[++i], "rate");
            } else if (arg == "--ramp" || arg == "-ra") {
                ramp = cliHelper::parseIntArg(argv[++i], "ramp");
            } else if (arg == "--spike" || arg == "-s") {
                spike = cliHelper::parseIntArg(argv[++i], "spike");
            } else if (arg == "--endpoint" || arg == "-e") {
                endpoint = argv[++i];
                // if (endpoint.empty()) throw std::runtime_error("Error: Endpoint value cannot be empty.");
            } else if (arg == "--payload" || arg == "-p") {
                payload = argv[++i];
                if (payload.empty()) throw std::runtime_error("Error: Payload value cannot be empty.");
            } else if (arg == "--verbose" || arg == "-v") {
                verbose = true;
            } else {
                throw std::runtime_error("Error: Unknown option '" + arg + "'. Use --help for usage.");
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            exit(1);
        }
    }

    if (target.empty()) throw std::runtime_error("Error: Target URL is required.");
    // if (endpoint.empty()) throw std::runtime_error("Error: API endpoint is required.");
}

int main(int argc, char* argv[]) {
    int numThreads = 1, payloadCount = 0, rateLimit = 0, ramp = 0, spike = 0;
    bool verbose = false;
    std::string target, endpoint, payload, requestType;

    try {
        parseArguments(argc, argv, numThreads, payloadCount, rateLimit, ramp, spike, target, endpoint, verbose, payload, requestType);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // Display program info
    std::cout << R"(
==========================================
 ____   _    ______   ______  _   _ ____  
|  _ \ / \  |  _ \ \ / /  _ \| | | / ___| 
| |_) / _ \ | |_) \ V /| |_) | | | \___ \ 
|  __/ ___ \|  __/ | | |  _ <| |_| |___) |
|_| /_/   \_\_|    |_| |_| \_\\___/|____/ 
==========================================
)";
    std::cout << "Threads: " << numThreads << "\nTarget: " << target << "\nEndpoint: " << endpoint
              << "\nRate Limit: " << rateLimit << " ms\n==========================================\n";
    
    signal(SIGINT, signalHandler);
    std::cout << "Program is running. Press Ctrl+C to stop.\n";

    // Launch threads
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(runWorkerThread, target, endpoint, verbose, payloadCount, rateLimit, ramp, spike, payload, requestType);
    }

    // Wait for threads to finish
    for (auto& thread : threads) {
        if (thread.joinable()) thread.join();
    }

    std::cout << "\nProgram has stopped.\n";
    return 0;
}
