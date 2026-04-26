#pragma once

#include "MonsterDescription.h"
#include <utility>
#include <vector>

struct WaveDescription {
    int rewardGold = 0;
    std::vector<std::pair<int, MonsterType>> waveInformation;
};
