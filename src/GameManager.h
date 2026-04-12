#pragma once
#include <vector>
#include <memory>
#include "IRoutine.h" // IRoutine은 순수 가상 함수만 있으므로 헤더만 있어도 무방함

class GameManager {
public:
    enum class GameState { Running, GameOver, Victory };

private:
    GameState currentState;
    std::vector<std::shared_ptr<IRoutine>> routines;
    std::vector<std::shared_ptr<IRoutine>> pendingAdds;

public:
    GameManager(); // 생성자 선언
    
    // 메서드 선언 (구현부는 없음)
    void addRoutine(std::shared_ptr<IRoutine> routine);
    void triggerGameOver();
    void triggerVictory();
    void tick();
};