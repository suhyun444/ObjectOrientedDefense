#pragma once
#include "IRoutine.h"
#include "WaveDescription.h"
#include "WaveParser.h"
#include <memory>
#include <string>
#include <vector>

class Monster;
class Path;
class Timer;

class Wave : public IRoutine {
private:
    int level;
    WaveDescription description;
    int spawnedCount;
    bool active;
    std::vector<std::shared_ptr<Monster>> monsters;
    const Path* path;
    Timer* timer;
    WaveParser parser;

public:
    Wave(const WaveDescription& description = WaveDescription{}, int level = 1);

    bool loadFromFile(const std::string& filePath);
    void setPath(const Path* path);
    void setTimer(Timer* timer);
    void setSpawnDelay(float delaySeconds);
    void spawnMonster();

    void update() override;
    bool isAlive() const override;
};
