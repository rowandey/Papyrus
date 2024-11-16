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
    myMatch.getChampNames();

    // Calls the getSummonerNames Instance Member function of class
    myMatch.getSummonerName();

    return 0;
}


