#include "payloadBuilder.hpp"

using json = nlohmann::json;

void payloadBuilder::setPayload(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file at " + filePath);
    }

    try {
        file >> payload; // Parse the file into a JSON object
    } catch (const json::parse_error& e) {
        throw std::runtime_error("Error: Failed to parse JSON. " + std::string(e.what()));
        std::abort();
    }
}

// Gets the payload as a JSON object
json payloadBuilder::getPayload() {
    return payload;
}