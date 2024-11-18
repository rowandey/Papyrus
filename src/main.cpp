#include <iostream>
#include "../include/match.hpp"
#include "../include/json.hpp"
using json = nlohmann::json;

int main() {

    // Creates a readable JSON object based off the match.json file passed to it
    std::ifstream f("match.json");
    json data = json::parse(f);

    // Declares the myMatch variable of type match which is our class
    match myMatch;
    // Defines the matches public data variable with the JSON object we created
    myMatch.data = data;

    // Calls the getRunes Instance Member function of the class
    myMatch.getRunes();

    //myMatch.getChampNames();
    //myMatch.getSummonerName();
    //myMatch.getItems();
    //myMatch.getSummoners();



    std::cout << "Random String: " << myRandom::generateRandomString(10) << std::endl;

    return 0;
}


