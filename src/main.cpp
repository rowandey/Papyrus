#include <iostream>
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
// #include "../include/apiClient.hpp"

using json = nlohmann::json;

int main() {

    // Creates a readable JSON object based off the match.json file passed to it
    // std::ifstream f("match.json");
    // json data = json::parse(f);

    matchBuilder randMatch;
    std::cout << randMatch.randomMatch().dump(4) << std::endl;

    return 0;
}


