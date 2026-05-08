#pragma once
#include <functional>

class Tower;
class Wave;

class Base {
private:
    int hp;
    int gold;
    bool alive;
    std::function<void()> onDeathCallback;

public:
    Base(std::function<void()> deathCallback);

    int getHp()   const;
    int getGold() const;

    void takeDamage(int damage);
    void addGold(int amount);
    bool useGold(int amount);

};
