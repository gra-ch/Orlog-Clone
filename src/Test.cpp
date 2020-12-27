#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> randI(0, 5);
    int dices[6] = {1, 2, 3, 4, 5, 6};

    for (size_t i = 0; i < 3; ++i)
    {
        cout << "Index: " << randI(generator) << endl;
        cout << dices[randI(generator)] << endl;
    }
}