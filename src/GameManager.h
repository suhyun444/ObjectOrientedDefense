#pragma once
#include <vector>
#include <memory>
#include "IRoutine.h"

class Base;
class Monster;

class GameManager {
public:
    enum class GameState { Running, GameOver, Victory };

private:
    GameState currentState;
    std::vector<std::shared_ptr<IRoutine>> routines;
    std::vector<std::shared_ptr<IRoutine>> pendingAdds;
    Base* base = nullptr;

public:
    GameManager();

    void setBase(Base* b);
    void dealDamageToBase(int damage);
    void addGoldToBase(int amount);

    void addRoutine(std::shared_ptr<IRoutine> routine);
    void triggerGameOver();
    void triggerVictory();
    void tick();
    std::vector<std::shared_ptr<Monster>> getAliveMonsters() const;
};
