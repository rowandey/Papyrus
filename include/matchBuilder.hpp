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
            //Imports the match template file that is gonna get copied, transformed, and returned
            std::ifstream file(templatePath);
            json matchTemplate = json::parse(file);
            
            // TODO: Need to have a proper set of random fields generated for the following
            matchTemplate["info"]["gameCreation"] = 9466848;
            matchTemplate["info"]["gameDuration"] = myRandom::generateRandomInt(900, 2700);
            matchTemplate["info"]["gameEndTimestamp"] = 9466848;
            // matchTemplate["info"]["gameId"] = "???";
            // matchTemplate["info"]["gameName"] = "???";
            matchTemplate["info"]["gameStartTimestamp"] = 9466848;

            // NA1_5145792127
            matchTemplate["metadata"]["matchId"] = "TEST1_" + myRandom::generateRandomNumberString(10);

            /*
            There is a problem that will occur here if you are not careful. If you do not pass the json
            object to the loop by reference, you will be altering a COPY of the matchTemplate and it will
            not work as intended.

             The original file of match-template.json is unaffected by any changes.
            */

            // Randomly determine win/loss for the different teams
            bool firstSetWin = myRandom::getRandomBool();
            bool secondSetWin = !firstSetWin;
            int participantIndex = 0;
            for (json& participant : matchTemplate["info"]["participants"]) {
                if (participantIndex < 5) {
                    participant["win"] = firstSetWin;
                } else {
                    participant["win"] = secondSetWin;
                }
                participantIndex++;
            }



            bool isFirstIteration = true;

            for (json& participant : matchTemplate["info"]["participants"]) {
                // 0-25 is a reasonable amount of kills and assists that 
                // can reasonably happen in League of Legends
                participant["assists"] = myRandom::generateRandomInt(0, 25);
                participant["deaths"] = myRandom::generateRandomInt(0, 25);
                participant["kills"] = myRandom::generateRandomInt(0, 25);

                // 20k~ gold is around full build
                participant["goldEarned"] = myRandom::generateRandomInt(1, 20000);
                participant["totalDamageDealtToChampions"] = myRandom::generateRandomInt(1, 90000);
                participant["totalMinionsKilled"] = myRandom::generateRandomInt(1, 200);
                participant["totalAllyJungleMinionsKilled"] = myRandom::generateRandomInt(1, 100);
                participant["totalEnemyJungleMinionsKilled"] = myRandom::generateRandomInt(1, 50);

                participant["champExperience"] = myRandom::generateRandomInt(1, 12576);
                participant["champLevel"] = myRandom::generateRandomInt(1, 18);
                participant["championId"] = myRandom::generateRandomInt(1, 200);
                participant["championName"] = getRandomChamp();

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

                // Random Summoner Name and Riot Account data
                if (isFirstIteration) {
                    participant["riotIdGameName"] = "bsawatestuser";
                    participant["riotIdTagline"] = "test";
                    participant["summonerName"] = "bsawatestuser";
                    isFirstIteration = false; // Ensure only the first iteration uses predefined strings
                } else {
                    participant["riotIdGameName"] = myRandom::generateRandomString(8);
                    participant["riotIdTagline"] = myRandom::generateRandomString(3);
                    participant["summonerName"] = myRandom::generateRandomString(8);
                }
            }

            return matchTemplate;
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

        std::string getRandomChamp() {
            std::ifstream champFile("../src/mappingFiles/champions.json");
            json championsJson = json::parse(champFile);

            // Stores the 'id' field values in a vector
            std::vector<std::string> champs;
            for (auto& champion : championsJson["data"].items()) {
                // Collect the 'id' value for each champion
                champs.push_back(champion.value()["id"]);
            }

            // Generate a random index
            std::random_device rd;  // Seed
            std::mt19937 gen(rd()); // Random number generator
            std::uniform_int_distribution<> distrib(0, champs.size() - 1);

            int randomIndex = distrib(gen);

            // Return the randomly selected champion id
            return champs[randomIndex];
        }

        // Gets a random key from a JSON file thats passed in. This is flexible 
        // for items, summoners, keystone runes, and secondary runes
        // They need to be IDs for use in MTRACK
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
