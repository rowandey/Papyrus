#include "match.hpp"

using json = nlohmann::json;

void match::getChampNames() {
    std::cout << "====================" << std::endl;
    std::cout << "Champion Names" << std::endl;
    std::cout << "--------------------" << std::endl;

    for (json i : data["info"]["participants"]) {
        std::cout << dropFirstAndLast(i["championName"]) << std::endl;
    }
}

// Get the Champion Names and the items they purchased in a game
void match::getItems() {
    std::cout << "====================" << std::endl;
    std::cout << "Item Names" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << std::endl;

    for (json i : data["info"]["participants"]) {
        std::cout << dropFirstAndLast(i["championName"]) << std::endl;
        std::cout << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item0"])) << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item1"])) << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item2"])) << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item3"])) << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item4"])) << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item5"])) << std::endl;
        std::cout << dropFirstAndLast(itemCodeToName(i["item6"])) << std::endl;
        std::cout << std::endl;
        std::cout << "----------" << std::endl;
    }
}

// Get the Summoner Spells for each participant
void match::getSummoners() {
    std::cout << "====================" << std::endl;
    std::cout << "Summoner Spells" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << std::endl;

    for (json i : data["info"]["participants"]) {
        std::cout << dropFirstAndLast(i["championName"]) << std::endl;
        std::cout << std::endl;
        std::cout << dropFirstAndLast(summonerCodeToName(i["summoner1Id"])) << std::endl;
        std::cout << dropFirstAndLast(summonerCodeToName(i["summoner2Id"])) << std::endl;
        std::cout << std::endl;
        std::cout << "----------" << std::endl;
    }
}

// Get the Keystone and the secondary rune for each participant
void match::getRunes() {
    std::cout << "====================" << std::endl;
    std::cout << "Runes Used" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << std::endl;

    for (json i : data["info"]["participants"]) {
        std::cout << dropFirstAndLast(i["championName"]) << std::endl;
        std::cout << std::endl;
        std::cout << keystoneCodeToName(i["perks"]["styles"][0]["selections"][0]["perk"]) << std::endl;
        std::cout << secondaryRuneCodeToName(i["perks"]["styles"][1]["style"]) << std::endl;
        std::cout << std::endl;
        std::cout << "----------" << std::endl;
    }
}

// Prints the summoner name of all players in the lobby
void match::getSummonerName() {
    std::cout << "====================" << std::endl;
    std::cout << "Summoner Names" << std::endl;
    std::cout << "--------------------" << std::endl;

    for (json i : data["info"]["participants"]) {
        std::cout << dropFirstAndLast(i["summonerName"]) << std::endl;
    }
}

// Internal function to remove the first and last characters from a string
std::string match::dropFirstAndLast(const std::string& str) {
    if (str.length() > 2) {
        return str.substr(1, str.length() - 2);
    }
    return ""; // Return an empty string if the input is too short
}

// Converts item codes to item names using a mapping file
std::string match::itemCodeToName(const int itemCode) {
    std::ifstream f("./mappingFiles/items.json");
    json items = json::parse(f);
    return items[std::to_string(itemCode)];
}

// Converts summoner spell codes to names using a mapping file
std::string match::summonerCodeToName(const int summonerCode) {
    std::ifstream f("./mappingFiles/summoners.json");
    json items = json::parse(f);
    return items[std::to_string(summonerCode)];
}

// Converts keystone rune codes to names using a mapping file
std::string match::keystoneCodeToName(const int runeCode) {
    std::ifstream f("./mappingFiles/keystones.json");
    json items = json::parse(f);
    return items[std::to_string(runeCode)];
}

// Converts secondary rune codes to names using a mapping file
std::string match::secondaryRuneCodeToName(const int runeCode) {
    std::ifstream f("./mappingFiles/secondaryRunes.json");
    json items = json::parse(f);
    return items[std::to_string(runeCode)];
}