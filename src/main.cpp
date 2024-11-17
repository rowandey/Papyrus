#include <iostream>
#include <fstream>
#include <string>

#include "../include/json.hpp"
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
};


int main() {

    // Creates a readable JSON object based off the match.json file passed to it
    std::ifstream f("match.json");
    json data = json::parse(f);

    // Declares the myMatch variable of type match which is our class
    match myMatch;

    // Defines the matches public data variable with the JSON object we created
    myMatch.data = data;

    
    // Calls the getChampionNames Instance Member function of class
    //myMatch.getChampNames();

    // Calls the getSummonerNames Instance Member function of class
    //myMatch.getSummonerName();

    // Calls the getItems Instance Member function of the class
    myMatch.getItems();

    return 0;
}


