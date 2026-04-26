#include "Player.h"
#include "Tower.h"
#include <iostream>

Player::Player(std::function<void()> deathCallback) 
    : hp(100), gold(0), alive(true), onDeathCallback(deathCallback) {}

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

bool Player::spendGold(int amount) {
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
        tower->upgradeLevel();
    }
}

void Player::removeTower(Tower* tower) {
    (void)tower;
}