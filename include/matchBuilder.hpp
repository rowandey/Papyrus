#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "json.hpp"
#include "myRandom.hpp"
using json = nlohmann::json;
/*
    Takes in a string and removes the first and last characters
    Will be used for removing the quotations from the champion names
*/

class matchBuilder {
    // Public data and publically accessible functions
    public:
        const std::string templatePath = "../src/mappingFiles/match-template.json";

        json randomMatch() {
            std::ifstream file(templatePath);
            json matchTemplate = json::parse(file);

            matchTemplate["info"]["gameCreation"] = "???";
            matchTemplate["info"]["gameDuration"] = "???";
            matchTemplate["info"]["gameEndTimestamp"] = "???";
            matchTemplate["info"]["gameId"] = "???";
            matchTemplate["info"]["gameName"] = "???";
            matchTemplate["info"]["gameStartTimestamp"] = "???";
            

            for(json participant : matchTemplate["info"]["participants"]){
                participant["assists"];
                participant["deaths"];
                participant["kills"];

                participant["goldEarned"];
                participant["totalDamageDealtToChampions"];
                participant["champExperience"];
                participant["champLevel"];
                participant["championId"];
                participant["championName"];

                participant["item0"] = getRandomItemFromJson();
                participant["item1"] = getRandomItemFromJson();
                participant["item2"] = getRandomItemFromJson();
                participant["item3"] = getRandomItemFromJson();
                participant["item4"] = getRandomItemFromJson();
                participant["item5"] = getRandomItemFromJson();
                participant["item6"] = getRandomItemFromJson();

                participant["summoner1Id"] = getRandomSummonerFromJson();
                participant["summoner2Id"] = getRandomSummonerFromJson();

                participant["perks"]["styles"][0]["selections"][0]["perk"] = getRandomKeystoneFromJson();
                participant["perks"]["styles"][1]["style"] = getRandomSecondaryRuneFromJson();

                participant["riotIdGameName"] = myRandom::generateRandomString(8);
                participant["riotIdTagline"] = std::string("#") + myRandom::generateRandomString(3);
                participant["summonerName"] = myRandom::generateRandomString(8);

            }

        }

        static std::string getRandomItemFromJson() {

            return getRandomFromJson("../src/mappingFiles/items.json");
            
        }

        static std::string getRandomSummonerFromJson() {

            return getRandomFromJson("../src/mappingFiles/summoners.json");
            
        }

        static std::string getRandomKeystoneFromJson() {

            return getRandomFromJson("../src/mappingFiles/keystones.json");

        }

        static std::string getRandomSecondaryRuneFromJson() {

            return getRandomFromJson("../src/mappingFiles/secondaryRunes.json");

        }

    
    // Internal use functions and data only   
    private:
        // The names in the match json are extracted with the quotation marks
        // Function removes the first and last characters of the string
        // Ex. "Ekko" -> Ekko
        std::string dropFirstAndLast(const std::string& str) {
            if (str.length() > 2) {
                return str.substr(0, str.length());
            }
            return ""; // Return an empty string if the input is too short
        }

        static std::string getRandomFromJson(const std::string& filename) {
            // Open and parse the JSON file
            std::ifstream file(filename);
            if (!file) {
                throw std::runtime_error("Failed to open the file: " + filename);
            }
            
            json items = json::parse(file);

            // Collect all the keys into a vector
            std::vector<std::string> keys;
            for (auto it = items.begin(); it != items.end(); ++it) {
                keys.push_back(it.key());
            }

            // Generate a random index
            std::random_device rd;  // Seed
            std::mt19937 gen(rd()); // Random number generator
            std::uniform_int_distribution<> distrib(0, keys.size() - 1);

            int randomIndex = distrib(gen);

            // Return the random key
            return keys[randomIndex];
        }

};
