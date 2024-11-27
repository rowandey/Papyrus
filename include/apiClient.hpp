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
    
    client.sendPOSTRequest();
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

    std::string sendGETRequest() {
        const std::string requestEndpoint = endpoint.empty() ? "/" : endpoint;
        auto res = client.Get(requestEndpoint.c_str());

        // Check if the response is valid before accessing any member
        if (res) {
            // Response is valid, now we can safely access res->status
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




    // TODO: Make a class method that sends a DELETE request too

    // TODO: Make a class method that sends a PUT request too

    // Send a POST request
    std::string sendPOSTRequest() {
        if (endpoint.empty()) {
            return "Error: Endpoint is not set.";
        }

        if (payload.empty()) {
            return "Error: Payload is not set.";
        }

        // Send the POST request
        auto res = client.Post(endpoint.c_str(), payload.dump(), "application/json");

        // Handle the response
        if (res) {
            if (res->status != 200) {
                return "Server returned error: " + res->status;
            } else if (res->status == 200) {
                return "200";
            }
        } else {
            return errorToString(res.error());
        }
    }

private:
    httplib::Client client; // HTTP client
    std::string serverAddress;   // Server address
    std::string endpoint;  // API endpoint
    json payload;          // JSON payload

    std::string errorToString(httplib::Error err) {
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
};