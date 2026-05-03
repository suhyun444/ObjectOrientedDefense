#include "Player.h"
#include "Tower.h"
#include <iostream>

Player::Player(std::function<void()> deathCallback)
    : hp(100), gold(10000), alive(true), onDeathCallback(deathCallback) {}

int Player::getHp()   const { return hp; }
int Player::getGold() const { return gold; }

void Player::takeDamage(int damage) {
    hp -= damage;
    std::cout << "Player Hit! Current HP: " << hp << "\n";
    if (hp <= 0 && alive)
    {
    alive = false;
        if (onDeathCallback)
        {
            onDeathCallback(); // 콜백 실행
        }
    }
}

void Player::addGold(int amount) {
    gold += amount;
}

bool Player::useGold(int amount) {
    if (gold < amount) {
        return false;
    }
    gold -= amount;
    return true;
}

void Player::buildTower(Tower* tower) {
    (void)tower;
}

void Player::upgradeTower(Tower* tower) {
    if (tower) {
        tower->upgrade();
    }
}

void Player::removeTower(Tower* tower) {
    (void)tower;
}

void Player::startWave(Wave* wave) {
    (void)wave;
}