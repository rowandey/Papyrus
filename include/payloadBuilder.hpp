#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class payloadBuilder {
    public:
        void setPayload(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw std::runtime_error("Error: Unable to open file at " + filePath);
            }

            try {
                file >> payload; // Parse the file into a JSON object
            } catch (const json::parse_error& e) {
                throw std::runtime_error("Error: Failed to parse JSON. " + std::string(e.what()));
            }
        }

        json getPayload () {
            return payload;
        }

    private:
        json payload = {};
};