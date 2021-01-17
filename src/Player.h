class Player {
private:
    unsigned int hp = 15;
    unsigned int gold = 0;

public:
    void setHp(int);
    int getHp();
    void addGold(int);
    int getGold();
};