#include "Wave.h"
#include "Monster.h"
#include "ObjectFactory.h"
#include <algorithm>
#include <fstream>
#include <iostream>

static const char* monsterTypeName(MonsterType t) {
    switch (t) {
        case MonsterType::Goblin:   return "Goblin";
        case MonsterType::Skeleton: return "Skeleton";
        case MonsterType::Wolf:     return "Wolf";
    }
    return "Unknown";
}

Wave::Wave(const Path* path)
    : level(0),
      spawnIndex(0),
      spawningComplete(true),
      rewardGiven(true),
      spawnTimer(0.f),
      path(path) {
    waveStartButton = ObjectFactory::getInstance().createWaveStartButton(this);
}

bool Wave::loadFromFile() {
    ++level;
    spawnIndex = 0;
    monsters.clear();
    rewardGiven = false;
    std::string filePath = "data/wave_" + std::to_string(level) + ".csv";
    description = parser.parseWave(filePath);

    if (description.hasError) {
        --level;
        std::cerr << "[CSV Error] " << description.errorMessage << "\n";
        ObjectFactory::getInstance().createErrorPopup();
        return false;
    }

    if (description.spawns.empty()) {
        --level;
        return false;
    }

    spawningComplete = false;

    std::string nextPath = "data/wave_" + std::to_string(level + 1) + ".csv";
    std::ifstream nextCheck(nextPath);
    isLastWave_ = !nextCheck.is_open();

    spawnTimer.reset(0.f);
    std::cout << "[Wave " << level << "] Start" << (isLastWave_ ? " (마지막 웨이브)" : "") << "\n";
    return true;
}

int Wave::GetLevel() const {
    return level;
}

void Wave::spawnMonster() {
    const SpawnEvent& ev = description.spawns[spawnIndex];

    auto monster = ObjectFactory::getInstance().createMonster(path, ev.type);
    monsters.push_back(monster);

    std::cout << "[Wave " << level << "] Spawn : " << monsterTypeName(ev.type)
              << " (" << (spawnIndex + 1) << "/" << description.spawns.size() << ")\n";

    ++spawnIndex;
    if (spawnIndex >= static_cast<int>(description.spawns.size())) {
        spawningComplete = true;
        std::cout << "[Wave " << level << "] All Monster Spawn Complete\n";
    }
}

bool Wave::isAllMonstersDefeated() const {
    for (const auto& m : monsters) {
        if (m->isAlive()) return false;
    }
    return true;
}

bool Wave::isComplete() const {
    return spawningComplete && isAllMonstersDefeated() && rewardGiven;
}

void Wave::setOnComplete(std::function<void(int)> callback) {
    onComplete = std::move(callback);
}

void Wave::setOnVictory(std::function<void()> callback) {
    onVictory = std::move(callback);
}

void Wave::update() {
    if (spawningComplete) {
        if (!rewardGiven && isAllMonstersDefeated()) {
            if (onComplete) onComplete(description.rewardGold);
            rewardGiven = true;
            if (isLastWave_) {
                if (onVictory) onVictory();
            }
        }
    } else {
        spawnTimer.tick();
        if (spawnTimer.isFinished()) {
            spawnMonster();
            if (!spawningComplete)
                spawnTimer.reset(description.spawns[spawnIndex].spawnTime);
        }
    }

    monsters.erase(
        std::remove_if(monsters.begin(), monsters.end(),
            [](const std::shared_ptr<Monster>& m) { return !m->isAlive(); }),
        monsters.end()
    );
}

bool Wave::isAlive() const {
    return true;
}
