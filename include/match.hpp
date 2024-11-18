#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "json.hpp"
using json = nlohmann::json;
/*
    Takes in a string and removes the first and last characters
    Will be used for removing the quotations from the champion names
*/

class match {
    // Public data and publically accessible functions
    public:
        // JSON object that will be passed in for processing
        json data;

        void getChampNames() {
            std::cout << "====================" << std::endl;
            std::cout << "Champion Names" << std::endl;
            std::cout << "--------------------" << std::endl;

            for(json i : data["info"]["participants"]){
                std::cout << dropFirstAndLast(i["championName"]) << std::endl;
            }
        }
        
        // If you want to get the Champion Names and the items they purchased in a game
        // Utilizes itemCodeToName() to convert the integers in the JSON to strings for
        //      processing
        void getItems() {
            std::cout << "====================" << std::endl;
            std::cout << "Item Names" << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << std::endl;
            
            for(json i : data["info"]["participants"]){
                
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

        // Instance Member Function gets the Summoner Spells for each participant
        void getSummoners() {
            std::cout << "====================" << std::endl;
            std::cout << "Summoner Spells" << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << std::endl;
            
            for(json i : data["info"]["participants"]){
                
                std::cout << dropFirstAndLast(i["championName"]) << std::endl;
                std::cout << std::endl;
                std::cout << dropFirstAndLast(summonerCodeToName(i["summoner1Id"])) << std::endl;
                std::cout << dropFirstAndLast(summonerCodeToName(i["summoner2Id"])) << std::endl;
                std::cout << std::endl;
                std::cout << "----------" << std::endl;
            }
        }

        // Instance Member Function gets the Keystone and the secondary school for each participant
        void getRunes() {
            std::cout << "====================" << std::endl;
            std::cout << "Runes Used" << std::endl;
            std::cout << "--------------------" << std::endl;
            std::cout << std::endl;
            
            for(json i : data["info"]["participants"]){
                std::cout << dropFirstAndLast(i["championName"]) << std::endl;
                std::cout << std::endl;
                std::cout << keystoneCodeToName(i["perks"]["styles"][0]["selections"][0]["perk"]) << std::endl;
                std::cout << secondaryRuneCodeToName(i["perks"]["styles"][1]["style"]) << std::endl;
                std::cout << std::endl;
                std::cout << "----------" << std::endl;
            }
        }
        
        // Prints the summer name of all players in the lobby
        void getSummonerName() {
            std::cout << "====================" << std::endl;
            std::cout << "Summoner Names" << std::endl;
            std::cout << "--------------------" << std::endl;
            
            for(json i : data["info"]["participants"]){
                std::cout << dropFirstAndLast(i["summonerName"]) << std::endl;
            }
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

        // Maps the integer item codes obtained from the match.json to a string
        // in the items.json file. Maps item codes to their string names 
        std::string itemCodeToName(const int itemCode) {
            std::ifstream f("./mappingFiles/items.json");
            json items = json::parse(f);
            return items[std::to_string(itemCode)];
        } 

        std::string summonerCodeToName(const int summonerCode) {
            std::ifstream f("./mappingFiles/summoners.json");
            json items = json::parse(f);
            return items[std::to_string(summonerCode)];
        } 

        std::string keystoneCodeToName(const int runeCode) {
            std::ifstream f("./mappingFiles/keystones.json");
            json items = json::parse(f);
            return items[std::to_string(runeCode)];
        }

        std::string secondaryRuneCodeToName(const int runeCode) {
            std::ifstream f("./mappingFiles/secondaryRunes.json");
            json items = json::parse(f);
            return items[std::to_string(runeCode)];
        }
};
