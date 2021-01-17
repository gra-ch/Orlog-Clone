#include "Player.h"

void Player::setHp(int hp) {
    Player::hp = hp;
}

int Player::getHp() {
    return hp;
}

void Player::addGold(int amount) {
    gold += amount;
}

int Player::getGold() {
    return gold;
}