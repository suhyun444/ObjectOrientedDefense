#pragma once

#include "WaveDescription.h"
#include "MonsterDescription.h"
#include <map>
#include <string>

class WaveParser {
public:
    WaveDescription parseWave(const std::string& waveFile);
    std::map<MonsterType, MonsterDescription> parseMonsterStats(const std::string& statsFile);

private:
    MonsterType parseMonsterType(const std::string& str);
};
