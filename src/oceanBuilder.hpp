#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "json.hpp"
#include "utilities.hpp"
#include "mapping.hpp"

using json = nlohmann::json;

class oceanBuilder {
public:
    // Function to generate a random match based on the template
    json randomOcean();

private:
    // Internal function to remove first and last characters from a string
    std::string dropFirstAndLast(const std::string& str);

    // Internal function to get a random key from a JSON file
    static std::string getRandomFromJson();
};

