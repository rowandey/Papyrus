#include <random>

class myRandom {
    public:
        static int generateRandomInt(int min, int max) {
            std::random_device rd;  // Seed source
            std::mt19937 gen(rd()); // Mersenne Twister RNG
            std::uniform_int_distribution<> distrib(min, max);
            return distrib(gen);

            /*
                Used as such:
                    int randomInt = generateRandomInt(1, 100); // Generate a random integer between 1 and 100
                    std::cout << "Random Integer: " << randomInt << std::endl;
            */
        }

        static std::string generateRandomString(size_t length) {
            const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            std::random_device rd;  // Seed source
            std::mt19937 gen(rd()); // Mersenne Twister RNG
            std::uniform_int_distribution<> distrib(0, chars.size() - 1);

            std::string randomStr;
            for (size_t i = 0; i < length; ++i) {
                randomStr += chars[distrib(gen)];
            }
            return randomStr;

            /*
                Used as such:
                    std::string randomStr = generateRandomString(10); // Generate a 10-character random string
                    std::cout << "Random String: " << randomStr << std::endl;
            */
        }

        static std::string generateRandomNumberString(size_t length) {
            const std::string chars = "0123456789";
            std::random_device rd;  // Seed source
            std::mt19937 gen(rd()); // Mersenne Twister RNG
            std::uniform_int_distribution<> distrib(0, chars.size() - 1);

            std::string randomStr;
            for (size_t i = 0; i < length; ++i) {
                randomStr += chars[distrib(gen)];
            }
            return randomStr;

            /*
                Used as such:
                    std::string randomStr = generateRandomNumberString(10); // Generate a 10-character random string
                    std::cout << "Random String: " << randomStr << std::endl;
            */
        }

        static bool getRandomBool() {
        // Seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        // Define the distribution for 0 or 1
        std::uniform_int_distribution<> distrib(0, 1);

        // Return true if random number is 1, else false
        return distrib(gen) == 1;
    }
};