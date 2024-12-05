#pragma once

#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

class ApiClient {
public:
    // Constructor to initialize the server address
    ApiClient(const std::string& serverAddress);

    // Set the API endpoint
    void setEndpoint(const std::string& endpoint);

    // Set the API parameter
    void setParameter(const std::string& parameter);

    // Set the JSON payload
    void setPayload(const json& payload);

    // Send GET request
    std::string sendGETRequest();

    // TODO: Method for DELETE request
    // TODO: Method for PUT request

    // Send POST request
    std::string sendPOSTRequest();

private:
    httplib::Client client; // HTTP client
    std::string serverAddress; // Server address
    std::string endpoint; // API endpoint
    std::string parameter; // API parameters
    json payload; // JSON payload

    // Error handling function
    std::string errorToString(httplib::Error err);
};