#include "Wave.h"
#include "Monster.h"
#include "Path.h"
#include "Timer.h"

Wave::Wave(const WaveDescription& description, int level)
        : level(level),
    description(description),
      spawnedCount(0),
      active(true),
    path(nullptr),
    timer(nullptr) {}

bool Wave::loadFromFile(const std::string& filePath) {
    return parser.loadFromFile(filePath);
}

void Wave::setPath(const Path* path) {
    this->path = path;
}

void Wave::setTimer(Timer* timer) {
}

void Wave::setSpawnDelay(float delaySeconds) {
}

void Wave::spawnMonster() {
    int totalCount = 0;
    for (const auto& info : description.waveInformation) {
        totalCount += info.first;
    }

    if (spawnedCount >= totalCount) {
        return;
    }

    auto monster = std::make_shared<Monster>();
    monster->setPath(path);
    monsters.push_back(monster);
    ++spawnedCount;
}

bool Wave::isFinished() const {
    int totalCount = 0;
    for (const auto& info : description.waveInformation) {
        totalCount += info.first;
    }

    if (spawnedCount < totalCount) {
        return false;
    }

    for (const auto& monster : monsters) {
        if (monster && monster->isAlive()) {
            return false;
        }
    }

    return true;
}

const std::vector<std::shared_ptr<Monster>>& Wave::getMonsters() const {
    return monsters;
}

void Wave::update() {
    if (!active) {
        return;
    }

    if (isFinished()) {
        active = false;
    }
}

bool Wave::isAlive() const {
    return active;
}
