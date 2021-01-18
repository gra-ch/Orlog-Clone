#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class Player {
private:
    unsigned int hp = 15;
    unsigned int gold = 0;

public:
    void setHp(int pass_hp) {
        hp = pass_hp;
    }

    int getHp() {
        return hp;
    }

    void addGold(int amount) {
        gold += amount;
    }

    int getGold() {
        return gold;
    }
};

int main() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> randOneToTen(0, 9);
    std::uniform_int_distribution<int> randOneToSix(0, 5);
    Player player1;
    Player player2;
    std::string allWays[10] = { "Axe", "Arrow", "Helmet", "Shield", "Steal", "Axe (Gold)", "Arrow (Gold)", "Helmet (Gold)", "Shield (Gold)", "Steal (Gold)" };
    std::string competitorDices[6] = { "Axe", "Arrow", "Helmet", "Shield", "Steal", "Axe (Gold)" };
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
    std::string input = "";
    unsigned int round = 0;
    while (round < 3 && allDices.size() != 0) {
        // push what dice faces it rolled out to rollOut array
        for (size_t i = 0; i < allDices.size(); ++i) {
            rollOut.emplace_back(allDices[i][randOneToSix(generator)]);
        }

        // display the dice faces
        for (std::vector<std::string>::const_iterator it = rollOut.begin(); it != rollOut.end(); ++it) {
            std::cout << "Dice " << it - rollOut.begin() + 1 << ": " << *it << std::endl;
        }

        std::cout << "You choose dice? : ";
        getline(std::cin, input);

        // split the input string into number
        std::istringstream ss(input);
        std::string word = "";
        std::vector<int> arr = {};
        std::vector<int> arr2 = {};
        while (ss >> word) {
            int x = std::stoi(word);
            arr.emplace_back(x - 1);
        }
        sort(arr.begin(), arr.end());

        // save the chosen dices and remove it from allDices
        for (size_t i = 0; i < arr.size(); ++i) {
            chosen.emplace_back(rollOut.at(arr[i]));
            allDices.erase(allDices.begin() + arr[i] - i);
        }

        ++round;
        rollOut.clear();
    }

    // display choosen disces
    std::cout << "You choose: ";
    for (std::vector<std::string>::const_iterator it = chosen.begin(); it != chosen.end(); ++it) {
        if (it - chosen.begin() == 5) {
            std::cout << *it;
        } else {
            std::cout << *it << ", ";
        }
    }
    std::cout << std::endl;

    // TODO: decide which side better

    // collect coins
    for (std::string& choose : chosen) {
        if (choose.find("(Gold)") != std::string::npos) {
            player1.addGold(1);
        }
    }

    if (player1.getHp() > player2.getHp()) {
        std::cout << "Player 1 wins";
    } else {
        std::cout << "Player 2 wins";
    }
}