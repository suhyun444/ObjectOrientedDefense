#include "Player.h"
#include <iostream>

Player::Player(std::function<void()> deathCallback) 
    : hp(100), alive(true), onDeathCallback(deathCallback) {}

void Player::takeDamage(int damage) {
    hp -= damage;
    std::cout << "Player Hit! Current HP: " << hp << "\n";
}

void Player::update() {
    if (hp <= 0 && alive) {
        alive = false;
        if (onDeathCallback) {
            onDeathCallback(); // 콜백 실행
        }
    }
}

bool Player::isAlive() const { 
    return alive; 
}