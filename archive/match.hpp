#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class match {
public:
    // Public data member that will be passed in for processing
    json data;

    // Public member functions to get information about participants
    void getChampNames();
    void getItems();
    void getSummoners();
    void getRunes();
    void getSummonerName();

private:
    // Private helper functions for internal processing

    // Removes the first and last characters of the string
    std::string dropFirstAndLast(const std::string& str);

    // Maps item codes to item names
    std::string itemCodeToName(const int itemCode);

    // Maps summoner codes to summoner spell names
    std::string summonerCodeToName(const int summonerCode);

    // Maps rune codes to keystone names
    std::string keystoneCodeToName(const int runeCode);

    // Maps rune codes to secondary rune names
    std::string secondaryRuneCodeToName(const int runeCode);
};
