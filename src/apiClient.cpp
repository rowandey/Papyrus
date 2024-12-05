#include "apiClient.hpp"

using json = nlohmann::json;

// Constructor to initialize the server address
ApiClient::ApiClient(const std::string& serverAddress) : client(serverAddress) {}

// Set the API endpoint
void ApiClient::setEndpoint(const std::string& endpoint) {
    this->endpoint = endpoint;
}

// Set the API parameter
void ApiClient::setParameter(const std::string& parameter) {
    this->parameter = parameter;
}

// Set the JSON payload
void ApiClient::setPayload(const json& payload) {
    this->payload = payload;
}

// Send a GET request
std::string ApiClient::sendGETRequest() {
    const std::string requestEndpoint = endpoint.empty() ? "/" : endpoint;
    const std::string requestParameter = parameter.empty() ? "" : parameter;
    std::string requestCombined = requestEndpoint + requestParameter;

    auto res = client.Get(requestCombined.c_str());

    // Check if the response is valid before accessing any member
    if (res) {
        int mystat = res->status;

        if (mystat == 200) {
            return "200"; // Successful response
        } else {
            return "Server returned error: " + std::to_string(mystat);
        }
    } else {
        // If response is invalid, handle the error case
        return "Error: " + errorToString(res.error());
    }
}

// Send a POST request
std::string ApiClient::sendPOSTRequest() {
    const std::string requestEndpoint = endpoint.empty() ? "/" : endpoint;
    const std::string requestParameter = parameter.empty() ? "" : parameter;
    std::string requestCombined = requestEndpoint + requestParameter;

    if (endpoint.empty()) {
        return "Error: Endpoint is not set.";
    }
    if (payload.empty()) {
        return "Error: Payload is not set.";
    }

    // Send the POST request
    auto res = client.Post(requestCombined.c_str(), payload.dump(), "application/json");

    // Handle the response
    if (res) {
        if (res->status != 200) {
            return "Server returned error: " + std::to_string(res->status);
        } else if (res->status == 200) {
            return "200"; // Success
        }
    } 
    return errorToString(res.error());
    
}

// Convert error enum to string
std::string ApiClient::errorToString(httplib::Error err) {
    switch (err) {
        case httplib::Error::Success:
            return "Success";
        case httplib::Error::Connection:
            return "Connection error";
        case httplib::Error::BindIPAddress:
            return "Bind IP address error";
        case httplib::Error::Read:
            return "Read error";
        case httplib::Error::Write:
            return "Write error";
        case httplib::Error::ExceedRedirectCount:
            return "Exceeded redirect count";
        case httplib::Error::Canceled:
            return "Request canceled";
        case httplib::Error::SSLConnection:
            return "SSL connection error";
        case httplib::Error::SSLLoadingCerts:
            return "SSL loading certificates error";
        case httplib::Error::SSLServerVerification:
            return "SSL server verification error";
        default:
            return "Unknown error";
    }
}
