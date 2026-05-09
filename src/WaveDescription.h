#pragma once

#include "MonsterDescription.h"
#include <vector>
#include <string>

struct SpawnEvent {
    float spawnTime;
    MonsterType type;
};

struct WaveDescription {
    int rewardGold = 0;
    std::vector<SpawnEvent> spawns;
    bool hasError = false;
    std::string errorMessage;
};
