#pragma once
#include <functional>

class Tower;
class Wave;

class Player {
private:
    int hp;
    int gold;
    bool alive;
    std::function<void()> onDeathCallback;

public:
    Player(std::function<void()> deathCallback);

    void takeDamage(int damage);
    void addGold(int amount);
    bool useGold(int amount);

    void buildTower(Tower* tower);
    void upgradeTower(Tower* tower);
    void removeTower(Tower* tower);
    void startWave(Wave* wave);

};