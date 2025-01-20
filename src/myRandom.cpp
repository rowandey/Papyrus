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

    constexpr char chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    constexpr size_t chars_len = sizeof(chars) - 1;

    static std::uniform_int_distribution<> distrib(0, chars_len - 1);
    std::string randomStr;
    randomStr.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        randomStr += chars[distrib(gen)];
    }
    return randomStr;

}

std::string myRandom::generateRandomNumberString(size_t length) {

    constexpr char chars[] = "0123456789";
    constexpr size_t chars_len = sizeof(chars) - 1;
    static std::uniform_int_distribution<> distrib(0, chars_len - 1);

    std::string randomStr;
    randomStr.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        randomStr += chars[distrib(gen)];
    }
    return randomStr;
}

bool myRandom::getRandomBool() {
    static std::uniform_int_distribution<> distrib(0, 1);

    // Return true if random number is 1, else false
    return distrib(gen) == 1;

}
