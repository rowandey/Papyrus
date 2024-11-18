#include <iostream>
#include "../include/match.hpp"
#include "../include/matchBuilder.hpp"
#include "../include/json.hpp"
#include "../include/apiClient.hpp"

using json = nlohmann::json;

int main() {

    // Creates a readable JSON object based off the match.json file passed to it
    std::ifstream f("match.json");
    json data = json::parse(f);

    // Declares the myMatch variable of type match which is our class
    // Defines the matches public data variable with the JSON object we created

    /*
    match myMatch;
    myMatch.data = data;
    myMatch.getRunes();
    myMatch.getChampNames();
    myMatch.getSummonerName();
    myMatch.getItems();
    myMatch.getSummoners();
    */

    std::cout << "Random Item Code: " << matchBuilder::getRandomItemFromJson() << std::endl;
    std::cout << "Random Item Code: " << matchBuilder::getRandomItemFromJson() << std::endl;
    std::cout << "Random Item Code: " << matchBuilder::getRandomItemFromJson() << std::endl;
    std::cout << "Random Item Code: " << matchBuilder::getRandomItemFromJson() << std::endl;
    std::cout << "Random Item Code: " << matchBuilder::getRandomItemFromJson() << std::endl;

    std::cout << "Random Summoner Code: " << matchBuilder::getRandomSummonerFromJson() << std::endl;
    std::cout << "Random Summoner Code: " << matchBuilder::getRandomSummonerFromJson() << std::endl;
    std::cout << "Random Summoner Code: " << matchBuilder::getRandomSummonerFromJson() << std::endl;
    std::cout << "Random Summoner Code: " << matchBuilder::getRandomSummonerFromJson() << std::endl;
    std::cout << "Random Summoner Code: " << matchBuilder::getRandomSummonerFromJson() << std::endl;

    std::cout << "Random Keystone Code: " << matchBuilder::getRandomKeystoneFromJson() << std::endl;
    std::cout << "Random Keystone Code: " << matchBuilder::getRandomKeystoneFromJson() << std::endl;
    std::cout << "Random Keystone Code: " << matchBuilder::getRandomKeystoneFromJson() << std::endl;
    std::cout << "Random Keystone Code: " << matchBuilder::getRandomKeystoneFromJson() << std::endl;
    std::cout << "Random Keystone Code: " << matchBuilder::getRandomKeystoneFromJson() << std::endl;

    std::cout << "Random Secondary Runes Code: " << matchBuilder::getRandomSecondaryRuneFromJson() << std::endl;
    std::cout << "Random Secondary Runes Code: " << matchBuilder::getRandomSecondaryRuneFromJson() << std::endl;
    std::cout << "Random Secondary Runes Code: " << matchBuilder::getRandomSecondaryRuneFromJson() << std::endl;
    std::cout << "Random Secondary Runes Code: " << matchBuilder::getRandomSecondaryRuneFromJson() << std::endl;
    std::cout << "Random Secondary Runes Code: " << matchBuilder::getRandomSecondaryRuneFromJson() << std::endl;

    return 0;
}


