#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

int main()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> randOneToTen(0, 9);
    uniform_int_distribution<int> randOneToSix(0, 5);
    unsigned int hp = 15;
    string allWays[10] = { "Axe", "Arrow", "Helmet", "Shield", "Steal", "Axe (Gold)", "Arrow (Gold)", "Helmet (Gold)", "Shield (Gold)", "Steal (Gold)" };
    vector<vector<string>> allDices;
    vector<string> rollOut = {};
    vector<string> chosen = {};

    // for (size_t i = 0; i < 6; ++i)
    // {
    //     cout << "Index: " << randI(generator) << endl;
    //     cout << "Result: " << dices[randI(generator)] << endl;
    // }

    for (size_t j = 0; j < 6; ++j) {
        vector<string> temp;
        for (size_t k = 0; k < 6; ++k) {
            temp.emplace_back(allWays[randOneToTen(generator)]);
        }
        allDices.emplace_back(temp);
    }

    for (size_t i = 0; i < 6; ++i) {
        rollOut.emplace_back(allDices[i][randOneToSix(generator)]);
    }

    for (vector<string>::const_iterator it = rollOut.begin(); it != rollOut.end(); ++it) {
        cout << "Dice " << it - rollOut.begin() + 1 << ": " << *it << endl;
    }

    unsigned int x = 10, round = 0;
    while (x != 0 && round < 3) {
        cout << "You choose dice? (Enter 0 to end this round): ";
        cin >> x;
        chosen.emplace_back(rollOut.at(x - 1));
        ++round;
    }

    cout << "You choose: ";
    for (vector<string>::const_iterator it = chosen.begin(); it != chosen.end(); ++it) {
        if (it - chosen.begin() == 2) {
            cout << *it;
        } else {
            cout << *it << ", ";
        }
    }
    cout << endl;
}