#pragma once

#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class payloadBuilder {
public:
    // Reads a JSON file from the provided file path and stores it into the payload object
    void setPayload(const std::string& filePath);

    // Returns the stored JSON payload
    json getPayload();

private:
    // Holds the parsed JSON payload
    json payload = {};
};
