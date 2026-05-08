#include "Base.h"
#include "Tower.h"
#include <iostream>

Base::Base(std::function<void()> deathCallback)
    : hp(3), gold(400), alive(true), onDeathCallback(deathCallback) {}

int Base::getHp()   const { return hp; }
int Base::getGold() const { return gold; }

void Base::takeDamage(int damage) {
    hp -= damage;
    std::cout << "Base Hit! Current HP: " << hp << "\n";
    if (hp <= 0 && alive)
    {
    alive = false;
        if (onDeathCallback)
        {
            onDeathCallback();
        }
    }
}

void Base::addGold(int amount) {
    gold += amount;
}

bool Base::useGold(int amount) {
    if (gold < amount) {
        return false;
    }
    gold -= amount;
    return true;
}
