#include "matchBuilder.hpp"

using json = nlohmann::json;

json matchBuilder::randomMatch() {
    // Imports the match template file that is going to get copied, transformed, and returned
    std::string templatePath = "mappingFiles/match-template.json";
    std::ifstream file(templatePath);
    json matchTemplate;
    try {
        matchTemplate = json::parse(file);
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON Parse Error: " << templatePath << e.what() << std::endl;
        // Handle the error or return early
    }

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

    bool isFirstIteration = true;

    for (json& participant : matchTemplate["info"]["participants"]) {
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

        participant["champExperience"] = myRandom::generateRandomInt(1, 12576);
        participant["champLevel"] = myRandom::generateRandomInt(1, 18);
        participant["championId"] = myRandom::generateRandomInt(1, 200);
        participant["championName"] = getRandomChamp();

        participant["item0"] = getRandomItemFromJson();
        participant["item1"] = getRandomItemFromJson();
        participant["item2"] = getRandomItemFromJson();
        participant["item3"] = getRandomItemFromJson();
        participant["item4"] = getRandomItemFromJson();
        participant["item5"] = getRandomItemFromJson();
        participant["item6"] = getRandomItemFromJson();

        participant["summoner1Id"] = getRandomSummonerFromJson();
        participant["summoner2Id"] = getRandomSummonerFromJson();

        participant["perks"]["styles"][0]["selections"][0]["perk"] = getRandomKeystoneFromJson();
        participant["perks"]["styles"][1]["style"] = getRandomSecondaryRuneFromJson();

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

// Static function to get a random item from the items.json file
std::string matchBuilder::getRandomItemFromJson() {
    return getRandomFromJson("mappingFiles/items.json");
}

// Static function to get a random summoner spell from the summoners.json file
std::string matchBuilder::getRandomSummonerFromJson() {
    return getRandomFromJson("mappingFiles/summoners.json");
}

// Static function to get a random keystone from the keystones.json file
std::string matchBuilder::getRandomKeystoneFromJson() {
    return getRandomFromJson("mappingFiles/keystones.json");
}

// Static function to get a random secondary rune from the secondaryRunes.json file
std::string matchBuilder::getRandomSecondaryRuneFromJson() {
    return getRandomFromJson("mappingFiles/secondaryRunes.json");
}

// Internal function to remove the first and last characters of a string
std::string matchBuilder::dropFirstAndLast(const std::string& str) {
    if (str.length() > 2) {
        return str.substr(1, str.length() - 2);
    }
    return ""; // Return an empty string if the input is too short
}

// Randomly selects a champion from the champions.json file
std::string matchBuilder::getRandomChamp() {
    std::ifstream champFile("mappingFiles/champions.json");

    json championsJson = json::parse(champFile);
    
    // Collect all champion ids
    std::vector<std::string> champs;
    for (auto& champion : championsJson["data"].items()) {
        champs.push_back(champion.value()["id"]);
    }

    // Generate a random index
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, champs.size() - 1);

    int randomIndex = distrib(gen);

    return champs[randomIndex]; // Return a random champion id
}

// Static helper function to get a random key from a given JSON file
std::string matchBuilder::getRandomFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open the file: " + filename);
    }

    json items = json::parse(file);

    // Collect all keys
    std::vector<std::string> keys;
    for (auto it = items.begin(); it != items.end(); ++it) {
        keys.push_back(it.key());
    }

    // Generate a random index
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, keys.size() - 1);

    int randomIndex = distrib(gen);

    return keys[randomIndex]; // Return a random key from the file
}