#pragma once
#include <string>
#include <memory>
#include "json.hpp"
#include <variant>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"


using json = nlohmann::json;

class ApiClient {
public:
    explicit ApiClient(const std::string& serverAddress);

    void setEndpoint(const std::string& endpoint);
    void setParameter(const std::string& parameter);
    void setPayload(const nlohmann::json& payload);

    std::string sendGETRequest();
    std::string sendPOSTRequest();

private:
    std::unique_ptr<httplib::Client> client;
    std::unique_ptr<httplib::SSLClient> sslClient;

    std::string endpoint;
    std::string parameter;
    nlohmann::json payload;

    std::string errorToString(httplib::Error err);
};