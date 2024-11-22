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

using json = nlohmann::json;

std::atomic<int> totalPayloadsSent(0);
bool isProgramActive = true;
std::mutex consoleMutex;  // Mutex for synchronizing console output

// Signal handler to gracefully stop the loop
void signalHandler(int signal) {
    std::cout << "Stopping program..." << std::endl;
    isProgramActive = false;
}

// Function that runs the logic in a single thread
void runWorkerThread(std::string targetURL, std::string endpoint, bool verbose) {
    // Declares the randMatch class so that we can build random games
    matchBuilder randMatch;

    // Defines the target server and API endpoint that we are going to blast
    ApiClient client(targetURL);
    client.setEndpoint(endpoint);
    
    if (verbose == true) {
        // Main loop that sends new requests
        while (isProgramActive) {
            // Builds and sends the payload containing the newly built random match
            client.setPayload(randMatch.randomMatch().dump(4));
            client.sendRequest();
            
            // Use the mutex to synchronize access to std::cout
            {
                std::lock_guard<std::mutex> guard(consoleMutex);  // Lock the mutex
                std::cout << targetURL << endpoint << "\tResponse: 200" << std::endl;
            }
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
        }
    }

    
}

int main(int argc, char* argv[]) {
    // Number of threads to run
    int numThreads = 1; // Default number of threads
    std::vector<std::thread> threads;
    std::string target = "";
    std::string endpoint = "";
    bool verbose = false;

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
            } else if (std::string(argv[i]) == "--endpoint" || std::string(argv[i]) == "-e") {
                if (i + 1 < argc) { // Ensure there's a next argument
                    endpoint = argv[++i]; // Set the target string
                    // Validate the target string if necessary
                    if (target.empty()) {
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
        threads.emplace_back(std::thread(runWorkerThread, target, endpoint, verbose));
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