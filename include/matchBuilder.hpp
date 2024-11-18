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
        // JSON object that will be passed in for processing
        json data;

        static std::string getRandomItemFromJson() {
            // Open and parse the JSON file
            std::ifstream file("../src/mappingFiles/items.json");
            if (!file) {
                throw std::runtime_error("Failed to open the file: ../src/mappingFiles/items.json");
            }

            json items;
            file >> items;

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

        static std::string getRandomSummonerFromJson() {
            // Open and parse the JSON file
            std::ifstream file("../src/mappingFiles/summoners.json");
            if (!file) {
                throw std::runtime_error("Failed to open the file: ../src/mappingFiles/summoners.json");
            }

            json items;
            file >> items;

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

        static std::string getRandomKeystoneFromJson() {
            // Open and parse the JSON file
            std::ifstream file("../src/mappingFiles/keystones.json");
            if (!file) {
                throw std::runtime_error("Failed to open the file: ../src/mappingFiles/keystones.json");
            }

            json items;
            file >> items;

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

        static std::string getRandomSecondaryRuneFromJson() {
            // Open and parse the JSON file
            std::ifstream file("../src/mappingFiles/secondaryRunes.json");
            if (!file) {
                throw std::runtime_error("Failed to open the file: ../src/mappingFiles/secondaryRunes.json");
            }

            json items;
            file >> items;

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


};
