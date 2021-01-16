#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> randOneToTen(0, 9);
    std::uniform_int_distribution<int> randOneToSix(0, 5);
    unsigned int hp = 15;
    std::string allWays[10] = { "Axe", "Arrow", "Helmet", "Shield", "Steal", "Axe (Gold)", "Arrow (Gold)", "Helmet (Gold)", "Shield (Gold)", "Steal (Gold)" };
    std::vector<std::vector<std::string>> allDices;
    std::vector<std::string> rollOut = {};
    std::vector<std::string> chosen = {};

    // init the player dices
    for (size_t j = 0; j < 6; ++j) {
        std::vector<std::string> temp;
        for (size_t k = 0; k < 6; ++k) {
            temp.emplace_back(allWays[randOneToTen(generator)]);
        }
        allDices.emplace_back(temp);
    }

    // asking player to pick out dices (each have 3 round)
    unsigned int x = -1, round = 0;
    while (x != 0 && round < 3) {
        // push what dice faces it rolled out to rollOut array
        for (size_t i = 0; i < 6; ++i) {
            rollOut.emplace_back(allDices[i][randOneToSix(generator)]);
        }

        // display the dice faces
        for (std::vector<std::string>::const_iterator it = rollOut.begin(); it != rollOut.end(); ++it) {
            std::cout << "Dice " << it - rollOut.begin() + 1 << ": " << *it << std::endl;
        }

        std::cout << "Enter 0 to end this round" << std::endl;
        std::cout << "You choose dice? (Enter 0 to end this round): ";
        std::cin >> x;
        chosen.emplace_back(rollOut.at(x - 1));

        // display choosen disces
        std::cout << "You choose: ";
        for (std::vector<std::string>::const_iterator it = chosen.begin(); it != chosen.end(); ++it) {
            if (it - chosen.begin() == 2) {
                std::cout << *it;
            } else {
                std::cout << *it << ", ";
            }
        }
        std::cout << std::endl;
        
        ++round;
    }
}