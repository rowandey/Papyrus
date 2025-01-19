#include "myRandom.hpp"

#include <string>
#include <random>

// Constructor to initialize the random number generator with a seed
std::random_device myRandom::rd;
std::mt19937 myRandom::gen(myRandom::rd());

int myRandom::generateRandomInt(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
    
}

std::string myRandom::generateRandomString(size_t length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;  // Seed source
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);

    std::string randomStr;
    for (size_t i = 0; i < length; ++i) {
        randomStr += chars[distrib(gen)];
    }
    return randomStr;
}

std::string myRandom::generateRandomNumberString(size_t length) {
    const std::string chars = "0123456789";
    std::random_device rd;  // Seed source
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);

    std::string randomStr;
    for (size_t i = 0; i < length; ++i) {
        randomStr += chars[distrib(gen)];
    }
    return randomStr;
}

bool myRandom::getRandomBool() {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    // Define the distribution for 0 or 1
    std::uniform_int_distribution<> distrib(0, 1);

    // Return true if random number is 1, else false
    return distrib(gen) == 1;
}
