#include <iostream>
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
#include "../include/apiClient.hpp"

using json = nlohmann::json;

int main() {

    // Creates a readable JSON object based off the match.json file passed to it
    // std::ifstream f("match.json");
    // json data = json::parse(f);

    matchBuilder randMatch;

    ApiClient client("http://10.0.0.11:80");
    client.setEndpoint("/addMatch");
    client.setPayload(randMatch.randomMatch().dump(4));
    client.sendRequest();
    std::cout << "Message request sent?" << std::endl;


    return 0;
}


