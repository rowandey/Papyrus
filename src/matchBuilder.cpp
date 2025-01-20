#include "matchBuilder.hpp"

#include <iostream>
#include <random>
#include <string>

#include "dependencies/json.hpp"
#include "mapping.hpp"
#include "myRandom.hpp"

using json = nlohmann::json;

// TODO: Inspect if its best practice to hardcode path to matchTemplate
json matchBuilder::randomMatch() {

    json matchTemplate;
    try {
        matchTemplate = json::parse(mapping::MATCH_TEMPLATE_JSON_MINIFIED);
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        // Handle the error or return early
    }
    

    // TODO: JSON payload can be parsed but structure is not validated

    matchTemplate["info"]["gameCreation"] = 9466848;
    matchTemplate["info"]["gameDuration"] = myRandom::generateRandomInt(900, 2700);
    matchTemplate["info"]["gameEndTimestamp"] = 9466848;
    matchTemplate["info"]["gameStartTimestamp"] = 9466848;

    matchTemplate["metadata"]["matchId"] = "TEST1_" + myRandom::generateRandomNumberString(10);

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

    // Used in assigning the first user to bsawatestuser#test
    bool isFirstIteration = true;

    // Batch fetching random values to save on runtime massively
    std::vector<std::string> participantItems = getRandomVectorFromJSON(mapping::ITEMS_JSON, 70);

    std::vector<std::string> participantChamp = getRandomVectorFromJSON(mapping::CHAMPIONS_JSON, 10);

    std::vector<std::string> participantSummoners = getRandomVectorFromJSON(mapping::SUMMMONERS_JSON, 20);

    std::vector<std::string> participantKeystone = getRandomVectorFromJSON(mapping::KEYSTONES_JSON, 10);

    std::vector<std::string> participantSecondary = getRandomVectorFromJSON(mapping::SECONDARY_RUNES_JSON, 10);

    // Will loop 10 times, once for each participant in game
    for (json& participant : matchTemplate["info"]["participants"]) {
        // std::vector<std::string> participantItems = getRandomItem(mapping::ITEMS_JSON, 7);

        // Randomly generate kills, assists, and other stats
        participant["assists"] = myRandom::generateRandomInt(0, 25);
        participant["deaths"] = myRandom::generateRandomInt(0, 25);
        participant["kills"] = myRandom::generateRandomInt(0, 25);

        // Randomize gold, damage, minion kills, etc.
        participant["goldEarned"] = myRandom::generateRandomInt(1, 20000);
        participant["totalDamageDealtToChampions"] = myRandom::generateRandomInt(1, 90000);
        participant["totalMinionsKilled"] = myRandom::generateRandomInt(1, 200);
        participant["totalAllyJungleMinionsKilled"] = myRandom::generateRandomInt(1, 100);
        participant["totalEnemyJungleMinionsKilled"] = myRandom::generateRandomInt(1, 50);

        // Randomizes Champ related data
        participant["champExperience"] = myRandom::generateRandomInt(1, 12576);
        participant["champLevel"] = myRandom::generateRandomInt(1, 18);
        participant["championId"] = myRandom::generateRandomInt(1, 200);

        participant["championName"] = participantChamp[0];
        participantChamp.erase(participantChamp.begin());

        // Randomizes items purchased
        for (int i = 0; i < 7; i++){
            std::string key = "item" + std::to_string(i);
            participant[key] = participantItems[0];
            participantItems.erase(participantItems.begin());
        }

        // Randomizes summoner spells
        participant["summoner1Id"] = participantSummoners[0];
        participantSummoners.erase(participantSummoners.begin());
        participant["summoner2Id"] = participantSummoners[0];
        participantSummoners.erase(participantSummoners.begin());

        // Randomizes keystone rune and secondary school
        participant["perks"]["styles"][0]["selections"][0]["perk"] = participantKeystone[0];
        participantKeystone.erase(participantKeystone.begin());

        participant["perks"]["styles"][1]["style"] = participantSecondary[0];
        participantSecondary.erase(participantSecondary.begin());

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

// Internal function to remove the first and last characters of a string
std::string matchBuilder::dropFirstAndLast(const std::string& str) {
    if (str.length() > 2) { return str.substr(1, str.length() - 2); }
    return ""; // Return an empty string if the input is too short
}

// Static helper function to get a random key from a given JSON file
std::string matchBuilder::getRandomFromJson(const std::string& jsonString) {
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


// Static helper function to get a random key from a given JSON file
std::vector<std::string> matchBuilder::getRandomVectorFromJSON(const std::string& jsonString, const int& count) {
    json items;

    std::vector<std::string> returnKeys;
    returnKeys.resize(count);

    try {
        items = json::parse(jsonString);
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error in getRandomFromJson: " << e.what() << std::endl;
        return {};
    }

    // Ensure the JSON is not empty
    if (items.empty()) {
        std::cerr << "Error: items JSON is empty!" << std::endl;
        return {};
    }

    if (!items.is_object()) {
        std::cerr << "Error: 'items' is not a valid JSON object!" << std::endl;
        return returnKeys;  // Exit or handle error
    }

    //std::cout << items.dump(4) << std::endl;

    // Collect all keys
    std::vector<std::string> keys;
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (!it.key().empty()) {
            // std::cout << "Key: " << it.key() << "\tValue: " << it.value() << std::endl;
            keys.push_back(it.key());
        } else {
            std::cerr << "Warning: Found an invalid key in the JSON object." << std::endl;
        }
    }

    // Check if the keys vector is empty
    if (keys.empty()) {
        std::cerr << "Error: No keys available in JSON object." << std::endl;
        return {};
    }

    // Generate a random index
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, keys.size() - 1);

    for (int i = 0; i < count; i++) {
        int randomIndex = distrib(gen);
        returnKeys[i] = keys[randomIndex];
    }

    return returnKeys; // Return a random key from the file
}