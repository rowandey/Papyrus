#include <iostream>
#include <string>
#include <random>
#include "../../src/json.hpp"

using json = nlohmann::json;

// Static helper function to get a random key from a given JSON file
std::string getRandomFromJson(const std::string& jsonString) {

    json items;

    try {
        items = json::parse(jsonString);
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error in getRandomFromJson: " << e.what() << std::endl;
        return "";
    }

    // Ensure the JSON is not empty
    if (items.empty()) {
        std::cerr << "Error: items JSON is empty!" << std::endl;
        return "";
    }

    // Collect all keys
    std::vector<std::string> keys;
    for (auto it = items.begin(); it != items.end(); ++it) {
        keys.push_back(it.key());
    }

    // Check if the keys vector is empty
    if (keys.empty()) {
        std::cerr << "Error: No keys available in JSON object." << std::endl;
        return "";
    }

    // Generate a random index
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, keys.size() - 1);
    int randomIndex = distrib(gen);

    return keys[randomIndex]; // Return a random key from the file
}

class TEST_getRandomFromJson {
    public:

    static int testValidJsonString () {

    }

    static int testInvalidJson () {
        
    }

    static int testNotStringPassed () {
        
    }
    
    static int testInvalidJsonNormalString () {
        
    }

    static int testRandomString () {
        
    }

    static int testEmptyString () {
        
    }
};