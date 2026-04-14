#pragma once
#include "IRoutine.h"
#include <functional>

class Player {
private:
    int hp;
    bool alive;
    std::function<void()> onDeathCallback;

public:
    // 생성자
    Player(std::function<void()> deathCallback);

    void takeDamage(int damage);
    
    // IRoutine 오버라이딩

};