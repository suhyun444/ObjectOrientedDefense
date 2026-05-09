#pragma once

#include "IRoutine.h"
#include "Timer.h"
#include "WaveDescription.h"
#include "WaveParser.h"
#include <functional>
#include <memory>
#include <vector>

class Monster;
class Path;

class WaveStartButton;
class Wave : public IRoutine {
private:
    int level;
    WaveDescription description;
    WaveParser parser;
    std::weak_ptr<WaveStartButton> waveStartButton;
    int spawnIndex;
    bool spawningComplete;
    bool rewardGiven;
    bool isLastWave_ = false;
    Timer spawnTimer;
    std::vector<std::shared_ptr<Monster>> monsters;
    const Path* path;
    std::function<void(int)> onComplete;
    std::function<void()> onVictory;

public:
    Wave(const Path* path);

    bool loadFromFile();
    bool isComplete() const;
    void setOnComplete(std::function<void(int)> callback);
    void setOnVictory(std::function<void()> callback);

    void update() override;
    bool isAlive() const override;
    int GetLevel() const;

private:
    void spawnMonster();
    bool isAllMonstersDefeated() const;
};
