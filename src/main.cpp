#include "common.hpp"

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    int numThreads = 1, payloadCount = 0, rateLimit = 0, ramp = 0, spike = 0;
    bool verbose = false;
    std::string target, endpoint, payload, parameter;

    try {
        cliHelper::parseArguments(argc, argv, numThreads, payloadCount, rateLimit, ramp, spike, target, endpoint, verbose, payload, parameter);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::abort();
        return 1;
    }

    // Prints the large PAPYRUS banner at the start of the program
    cliHelper::printBanner();

    std::cout << "Threads: " << numThreads << "\nTarget: " << target << "\nEndpoint: " << endpoint
              << "\nRate Limit: " << rateLimit << " ms\n==========================================\n";
    
    signal(SIGINT, threadWorks::signalHandler);
    std::cout << "Program is running. Press Ctrl+C to stop.\n";

    // Launch threads
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(&threadWorks::runWorkerThread, target, endpoint, verbose, payloadCount, rateLimit, ramp, spike, payload, parameter);
    }

    // Wait for threads to finish
    for (auto& thread : threads) {
        if (thread.joinable()) thread.join();
    }

    std::cout << "\nProgram has stopped.\n";
    return 0;
}
