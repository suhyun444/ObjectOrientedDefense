#pragma once

#include "MonsterDescription.h"
#include <vector>

struct SpawnEvent {
    float spawnTime;
    MonsterType type;
};

struct WaveDescription {
    int rewardGold = 0;
    std::vector<SpawnEvent> spawns;
};
