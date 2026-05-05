#include "GameManager.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <algorithm>

// 생성자 초기화
GameManager::GameManager() : currentState(GameState::Running) {}

void GameManager::setPlayer(Player* p) {
    player = p;
}

void GameManager::dealDamageToPlayer(int damage) {
    if (currentState != GameState::Running) return;
    if (player) player->takeDamage(damage);
}

void GameManager::addGoldToPlayer(int amount) {
    if (currentState != GameState::Running) return;
    if (player) player->addGold(amount);
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

std::vector<std::shared_ptr<Monster>> GameManager::getAliveMonsters() const {
    std::vector<std::shared_ptr<Monster>> result;
    for (const auto& r : routines) {
        if (auto m = std::dynamic_pointer_cast<Monster>(r))
            if (m->isAlive()) result.push_back(m);
    }
    for (const auto& r : pendingAdds) {
        if (auto m = std::dynamic_pointer_cast<Monster>(r))
            if (m->isAlive()) result.push_back(m);
    }
    return result;
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