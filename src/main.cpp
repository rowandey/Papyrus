#include <iostream>
#include <fstream>
#include <string>

#include "../include/json.hpp"
using json = nlohmann::json;
/*
    Takes in a string and removes the first and last characters
    Will be used for removing the quotations from the champion names
*/
std::string dropFirstAndLast(const std::string& str) {
    if (str.length() > 2) {
        return str.substr(0, str.length());
    }
    return ""; // Return an empty string if the input is too short
}

int getChampNames(json data) {
    
    for(json i : data["info"]["participants"]){
        std::cout << dropFirstAndLast(i["championName"]) << std::endl;
        //std::cout << i["championName"] << std::endl;
    }
    return 0;
}

int main() {
    //std::cout << "Hello world!" << std::endl;

    std::ifstream f("match.json");
    json data = json::parse(f);

    getChampNames(data);

    return 0;
}

