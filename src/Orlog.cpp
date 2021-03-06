#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

class Dices {
private:
    std::default_random_engine generator;
    std::vector<std::vector<std::string>> allDices;

public:
    friend class Player;

    // init the player dices
    Dices(unsigned int seed, std::string (&allWays)[10])
        : generator(seed) {
        std::uniform_int_distribution<int> randOneToTen(0, 9);
        for (size_t j = 0; j < 6; ++j) {
            std::vector<std::string> temp;
            for (size_t k = 0; k < 6; ++k) {
                temp.emplace_back(allWays[randOneToTen(generator)]);
            }
            allDices.emplace_back(temp);
        }
    }
};

class Player {
private:
    std::string name;
    Dices diceGrp;
    std::vector<std::string> rollOut = {};
    std::vector<std::string> chosen = {};
    unsigned int hp = 15;
    unsigned int gold = 10;
    unsigned int round = 0;
    std::map<std::string, int> marks {
        { "Axe", 0 },
        { "Arrow", 0 },
        { "Helmet", 0 },
        { "Shield", 0 },
        { "Steal", 0 },
    };

public:
    Player(unsigned int seed, std::string (&allWays)[10], std::string name)
        : diceGrp(seed, allWays)
        , name(name) { }

    std::string getName() {
        return name;
    }

    void setHp(int pass_hp) {
        hp = pass_hp;
    }

    int getHp() {
        return hp;
    }

    void addGold(int amount) {
        ++gold;
    }

    int getGold() {
        return gold;
    }

    void addRound() {
        ++round;
    }

    int getRound() {
        return round;
    }

    void addMark(std::string way) {
        marks[way] += 1;
    }

    std::map<std::string, int> getMarks() {
        return marks;
    }

    // push what dice faces it rolled out to rollOut array
    void rollDices() {
        rollOut.clear();
        std::uniform_int_distribution<int> randOneToSix(0, 5);
        for (size_t i = 0; i < diceGrp.allDices.size(); ++i) {
            rollOut.emplace_back(diceGrp.allDices[i][randOneToSix(diceGrp.generator)]);
        }
    }

    std::vector<std::vector<std::string>> getAllDices() {
        return diceGrp.allDices;
    }

    // save the chosen dices and remove it from allDices
    void saveChoice(std::vector<int>& arr) {
        for (size_t i = 0; i < arr.size(); ++i) {
            chosen.emplace_back(rollOut.at(arr[i]));
            diceGrp.allDices.erase(diceGrp.allDices.begin() + arr[i] - i);
        }
        if (round == 2 && chosen.size() < 6) {
            for (auto&& item : rollOut) {
                chosen.emplace_back(item);
            }
            diceGrp.allDices.clear();
        }
    }

    // display the dice faces and ask for input
    void prompt() {
        for (std::vector<std::string>::const_iterator it = rollOut.begin(); it != rollOut.end(); ++it) {
            std::cout << "Dice " << it - rollOut.begin() + 1 << ": " << *it << std::endl;
        }
        std::cout << name << " choose dice? : ";
    }

    // display choosen disces
    void display() {
        std::cout << name << " choose: ";
        for (std::vector<std::string>::const_iterator it = chosen.begin(); it != chosen.end(); ++it) {
            if (it - chosen.begin() == 5) {
                std::cout << *it;
            } else {
                std::cout << *it << ", ";
            }
        }
        std::cout << std::endl;
    }

    // DONE: collect the marks
    void collectMarks(std::string (&noGoldWays)[5]) {
        for (std::string& way : noGoldWays) {
            for (std::string& choose : chosen) {
                if (choose.find(way) != std::string::npos) {
                    addMark(way);
                }
            }
        }
    }

    // collect coins
    void collectGold() {
        for (std::string& choose : chosen) {
            if (choose.find("(Gold)") != std::string::npos) {
                addGold(1);
            }
        }
    }
};

int main() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::string allWays[10] = { "Axe", "Arrow", "Helmet", "Shield", "Steal", "Axe (Gold)", "Arrow (Gold)", "Helmet (Gold)", "Shield (Gold)", "Steal (Gold)" };
    std::string noGoldWays[5] = { "Axe", "Arrow", "Helmet", "Shield", "Steal" };
    Player player1(seed, allWays, "Player 1");
    Player player2(seed, allWays, "Player 2");
    Player order[2] = { player1, player2 };
    std::string competitorDices[6] = { "Axe", "Arrow", "Helmet", "Shield", "Steal", "Axe (Gold)" };
    // DONE: create dice class and put these to player class

    // asking player to pick out dices (each have 3 round)
    std::string input = "";
    for (auto&& player : order) {
        std::cout << "<---- It is " << player.getName() << " turn ---->" << std::endl;
        while (player.getRound() < 3 && player.getAllDices().size() != 0) {
            player.rollDices();
            player.prompt();
            getline(std::cin, input);
            // split the input string into number
            std::istringstream ss(input);
            std::string word = "";
            std::vector<int> arr = {};
            while (ss >> word) {
                int x = std::stoi(word);
                arr.emplace_back(x - 1);
            }
            sort(arr.begin(), arr.end());
            player.saveChoice(arr);
            player.addRound();
        }
        player.display();
        player.collectMarks(noGoldWays);
        player.collectGold();
    }

    // DONE: decide which side better
    if (player1.getMarks()["Axe"] > player2.getMarks()["Helmet"]) {
        player2.setHp(player2.getHp() - (player1.getMarks()["Axe"] - player2.getMarks()["Helmet"]));
    }
    if (player1.getMarks()["Arrow"] > player2.getMarks()["Shield"]) {
        player2.setHp(player2.getHp() - (player1.getMarks()["Arrow"] - player2.getMarks()["Shield"]));
    }
    player1.addGold(-player2.getMarks()["Steal"]);
    if (player2.getMarks()["Axe"] > player1.getMarks()["Helmet"]) {
        player1.setHp(player1.getHp() - (player2.getMarks()["Axe"] - player1.getMarks()["Helmet"]));
    }
    if (player2.getMarks()["Arrow"] > player1.getMarks()["Shield"]) {
        player1.setHp(player1.getHp() - (player2.getMarks()["Arrow"] - player1.getMarks()["Shield"]));
    }
    player2.addGold(-player1.getMarks()["Steal"]);

    if (player1.getHp() == player2.getHp()) {
        std::cout << "Draw!" << std::endl;
    } else if (player1.getHp() > player2.getHp()) {
        std::cout << "Player 1 wins!" << std::endl;
    } else {
        std::cout << "Player 2 wins!" << std::endl;
    }
}