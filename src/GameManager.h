#pragma once
#include <vector>
#include <memory>
#include "IRoutine.h"

class GameManager {
public:
    enum class GameState { Running, GameOver, Victory };

private:
    GameState currentState;
    std::vector<std::shared_ptr<IRoutine>> routines;
    std::vector<std::shared_ptr<IRoutine>> pendingAdds;

public:
    GameManager();
    

    void addRoutine(std::shared_ptr<IRoutine> routine);
    void triggerGameOver();
    void triggerVictory();
    void tick();
};