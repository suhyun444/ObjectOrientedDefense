#pragma once

#include "IRoutine.h"
#include "WaveDescription.h"
#include "WaveParser.h"
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
    float spawnElapsed;
    std::vector<std::shared_ptr<Monster>> monsters;
    const Path* path;

public:
    Wave(const Path* path);

    bool loadFromFile();
    bool isComplete() const;

    void update() override;
    bool isAlive() const override;
    int GetLevel() const;

private:
    void spawnMonster();
    bool isAllMonstersDefeated() const;
};
