#include <iostream>
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
#include "../include/apiClient.hpp"
#include <csignal>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <cmath>

using json = nlohmann::json;

std::atomic<int> totalPayloadsSent(0);
bool isProgramActive = true;
std::mutex consoleMutex;  // Mutex for synchronizing console output

// Signal handler to gracefully stop the loop
void signalHandler(int signal) {
    std::cout << "\nStopping program..." << std::endl;
    isProgramActive = false;
}

bool isValidInt(double num) {
    return std::floor(num) == num && num >= INT_MIN && num <= INT_MAX;
}

// Function that runs the logic in a single thread
void runWorkerThread(std::string targetURL, std::string endpoint, bool verbose, int payloadCount = 0, int rateLimit = 0) {
    // Declares the randMatch class so that we can build random games
    matchBuilder randMatch;

    // Defines the target server and API endpoint that we are going to blast
    ApiClient client(targetURL);
    client.setEndpoint(endpoint);

    if (payloadCount == 0){
        if (verbose == true) {
            // Main loop that sends new requests
            while (isProgramActive) {
                // Builds and sends the payload containing the newly built random match
                client.setPayload(randMatch.randomMatch().dump(4));
                
                // Use the mutex to synchronize access to std::cout
                {
                    std::lock_guard<std::mutex> guard(consoleMutex);  // Lock the mutex
                    std::cout << client.sendRequest() << std::endl;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(rateLimit));
            }
        }
        else {
            // Main loop that sends new requests
            while (isProgramActive) {
                // Builds and sends the payload containing the newly built random match
                client.setPayload(randMatch.randomMatch().dump(4));
                client.sendRequest();

                // Use the mutex to synchronize access to std::cout
                {
                    std::lock_guard<std::mutex> guard(consoleMutex);  // Lock the mutex
                    totalPayloadsSent++;
                    std::cout << "\rPayloads sent: " << totalPayloadsSent << std::flush;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(rateLimit));
            }
        }
    } else {
        if (verbose == true) {
            // Main loop that sends new requests
            while (isProgramActive) {
                // Builds and sends the payload containing the newly built random match
                client.setPayload(randMatch.randomMatch().dump(4));
                client.sendRequest();
                
                // Use the mutex to synchronize access to std::cout
                {
                    std::lock_guard<std::mutex> guard(consoleMutex);  // Lock the mutex
                    std::cout << client.sendRequest() << std::endl;
                }

                payloadCount--;
                if (payloadCount == 0) {
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(rateLimit));
            }
        }
        else {
            // Main loop that sends new requests
            while (isProgramActive) {
                // Builds and sends the payload containing the newly built random match
                client.setPayload(randMatch.randomMatch().dump(4));
                client.sendRequest();

                // Use the mutex to synchronize access to std::cout
                {
                    std::lock_guard<std::mutex> guard(consoleMutex);  // Lock the mutex
                    totalPayloadsSent++;
                    std::cout << "\rPayloads sent: " << totalPayloadsSent << std::flush;
                }

                payloadCount--;
                if (payloadCount == 0) {
                    break;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(rateLimit));
            }
        }
    }
    

    
}


// TODO: Add flag that lets you choose how many payloads you want to send
int main(int argc, char* argv[]) {
    // Number of threads to run
    int numThreads = 1; // Default number of threads
    int payloadCount = 0;
    std::vector<std::thread> threads;
    std::string target = "";
    std::string endpoint = "";
    bool verbose = false;
    int rateLimit = 0; // IN MILLISECONDS

    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
                std::cout << "Usage: ./{program-name} -{flag} {value}\n";
                return 0;
            } else if (std::string(argv[i]) == "--threads" || std::string(argv[i]) == "-th") {
                if (i + 1 < argc) { // Ensure there's a next argument
                    try {
                        numThreads = std::stoi(argv[++i]); // Parse the next argument
                    } catch (const std::invalid_argument&) {
                        std::cerr << "Error: Not a valid number for threads. Must be a positive integer.\n";
                        return 1;
                    } catch (const std::out_of_range&) {
                        std::cerr << "Error: Number out of range for threads.\n";
                        return 1;
                    }
                } else {
                    std::cerr << "Error: Missing value for --threads or -t.\n";
                    return 1;
                }
            } else if (std::string(argv[i]) == "--target" || std::string(argv[i]) == "-ta") {
                if (i + 1 < argc) { // Ensure there's a next argument
                    target = argv[++i]; // Set the target string
                    // Validate the target string if necessary
                    if (target.empty()) {
                        std::cerr << "Error: Target value cannot be empty.\n";
                        return 1;
                    }
                    // Additional string validation (if needed)
                } else {
                    std::cerr << "Error: Missing value for --target or -ta.\n";
                    return 1;
                }
            } else if (std::string(argv[i]) == "--count" || std::string(argv[i]) == "-c") {
                if (i + 1 < argc) { // Ensure there's a next argument
                    payloadCount = std::stoi(argv[++i]); // Set the target string
                    // Validate the target string if necessary
                    if (isValidInt(payloadCount) != 1) {
                        std::cerr << "Error: count value cannot be empty.\n";
                        return 1;
                    }
                    // Additional string validation (if needed)
                } else {
                    std::cerr << "Error: Missing value for --count or -c.\n";
                    return 1;
                }
            } else if (std::string(argv[i]) == "--rate" || std::string(argv[i]) == "-r") {
                if (i + 1 < argc) { // Ensure there's a next argument
                    rateLimit = std::stoi(argv[++i]); // Set the target string
                    // Validate the target string if necessary
                    if (isValidInt(rateLimit) != 1) {
                        std::cerr << "Error: rate value cannot be empty.\n";
                        return 1;
                    }
                    // Additional string validation (if needed)
                } else {
                    std::cerr << "Error: Missing value for --rate or -r.\n";
                    return 1;
                }
            } else if (std::string(argv[i]) == "--endpoint" || std::string(argv[i]) == "-e") {
                if (i + 1 < argc) { // Ensure there's a next argument
                    endpoint = argv[++i]; // Set the target string
                    // Validate the target string if necessary
                    if (endpoint.empty()) {
                        std::cerr << "Error: endpoint value cannot be empty.\n";
                        return 1;
                    }
                    // Additional string validation (if needed)
                } else {
                    std::cerr << "Error: Missing value for --endpoint or -e.\n";
                    return 1;
                }
            } else if (std::string(argv[i]) == "--verbose" || std::string(argv[i]) == "-v") {
                verbose = true;
            }
        }
    }

    std::cout << "==========================================" << std::endl;
    std::cout << " ____   _    ______   ______  _   _ ____  \n";
    std::cout << "|  _ \\ / \\  |  _ \\ \\ / /  _ \\| | | / ___| \n";
    std::cout << "| |_) / _ \\ | |_) \\ V /| |_) | | | \\___ \\ \n";
    std::cout << "|  __/ ___ \\|  __/ | | |  _ <| |_| |___) |\n";
    std::cout << "|_| /_/   \\_\\_|    |_| |_| \\_\\\\___/|____/ \n";
    std::cout << "==========================================" << std::endl;
    std::cout << "Threads in use: " << numThreads << std::endl;
    std::cout << "Target: " << target << std::endl;
    std::cout << "Endpoint: " << endpoint << std::endl;
    std::cout << "==========================================" << std::endl;

    // Attach the signal handler to interrupt signals
    std::signal(SIGINT, signalHandler);
    std::cout << "Program is running. Press Ctrl+C to stop." << std::endl;

    
    // Launch multiple threads
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(std::thread(runWorkerThread, target, endpoint, verbose, payloadCount, rateLimit));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    std::cout << "\nProgram has stopped." << std::endl;
    return 0;
}