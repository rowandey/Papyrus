#include "httplib.h"
#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

/*
Usage of the class:

    ApiClient client("https://example.com");
    
    client.setEndpoint("/api/users");
    
    json payload = {
        {"name", "Jane Doe"},
        {"email", "jane.doe@example.com"},
        {"age", 28}
    };
    
    client.setPayload(payload);
    
    client.sendRequest();
*/

class ApiClient {
public:
    // Constructor to initialize the server address
    ApiClient(const std::string& serverAddress) : client(serverAddress) {}

    // Set the API endpoint
    void setEndpoint(const std::string& endpoint) {
        this->endpoint = endpoint;
    }

    // Set the JSON payload
    void setPayload(const json& payload) {
        this->payload = payload;
    }

    // Send a POST request
    void sendRequest() {
        if (endpoint.empty()) {
            std::cerr << "Error: Endpoint is not set." << std::endl;
            return;
        }

        if (payload.empty()) {
            std::cerr << "Error: Payload is not set." << std::endl;
            return;
        }

        // Send the POST request
        auto res = client.Post(endpoint.c_str(), payload.dump(), "application/json");

        // Handle the response
        if (res) {
            if (res->status != 200) {
                std::cerr << "Server returned error: " << res->status << std::endl;
            }
        } else {
            std::cerr << "Request failed: " << res.error() << std::endl;
        }
    }

private:
    httplib::Client client; // HTTP client
    std::string endpoint;  // API endpoint
    json payload;          // JSON payload
};