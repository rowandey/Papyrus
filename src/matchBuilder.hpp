#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "json.hpp"
#include "utilities.hpp"
#include "mapping.hpp"

using json = nlohmann::json;

class matchBuilder {
public:
    // Function to generate a random match based on the template
    json randomMatch();

    // Static functions to get random items, summoners, keystones, and secondary runes from JSON files
    static std::string getRandomItemFromJson();
    static std::string getRandomSummonerFromJson();
    static std::string getRandomKeystoneFromJson();
    static std::string getRandomSecondaryRuneFromJson();

private:
    // Internal function to remove first and last characters from a string
    std::string dropFirstAndLast(const std::string& str);

    // Internal function to get a random champion from the champions JSON file
    std::string getRandomChamp();

    // Internal function to get a random key from a JSON file
    static std::string getRandomFromJson(const std::string& filename);
};

