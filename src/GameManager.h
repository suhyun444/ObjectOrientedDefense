#pragma once
#include <vector>
#include <memory>
#include "IRoutine.h"

class Player;
class Monster;

class GameManager {
public:
    enum class GameState { Running, GameOver, Victory };

private:
    GameState currentState;
    std::vector<std::shared_ptr<IRoutine>> routines;
    std::vector<std::shared_ptr<IRoutine>> pendingAdds;
    Player* player = nullptr;

public:
    GameManager();

    void setPlayer(Player* p);
    void dealDamageToPlayer(int damage);

    void addRoutine(std::shared_ptr<IRoutine> routine);
    void triggerGameOver();
    void triggerVictory();
    void tick();
    std::vector<std::shared_ptr<Monster>> getAliveMonsters() const;
};