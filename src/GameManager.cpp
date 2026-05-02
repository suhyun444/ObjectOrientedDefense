#include "GameManager.h"
#include "Player.h"
#include <iostream>
#include <algorithm>

// 생성자 초기화
GameManager::GameManager() : currentState(GameState::Running) {}

void GameManager::setPlayer(Player* p) {
    player = p;
}

void GameManager::dealDamageToPlayer(int damage) {
    if (player) player->takeDamage(damage);
}

void GameManager::addRoutine(std::shared_ptr<IRoutine> routine) {
    pendingAdds.push_back(routine);
}

void GameManager::triggerGameOver() {
    currentState = GameState::GameOver;
    std::cout << "[System] Game Over! 모든 업데이트를 중단하고 팝업을 띄웁니다.\n";
}

void GameManager::triggerVictory() {
    currentState = GameState::Victory;
    std::cout << "[System] Victory! 모든 업데이트를 중단하고 팝업을 띄웁니다.\n";
}

void GameManager::tick() {
    if (currentState != GameState::Running) return;

    if (!pendingAdds.empty()) {
        routines.insert(routines.end(), pendingAdds.begin(), pendingAdds.end());
        pendingAdds.clear();
    }

    for (auto& routine : routines) {
        if (routine->isAlive()) {
            routine->update();
        }
    }

    routines.erase(
        std::remove_if(routines.begin(), routines.end(),
            [](const std::shared_ptr<IRoutine>& r) { return !r->isAlive(); }),
        routines.end()
    );
}