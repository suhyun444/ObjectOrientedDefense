#pragma once

#include "WaveDescription.h"
#include <string>

class WaveParser {
public:
    WaveDescription parseWave(const std::string& waveFile);

private:
    MonsterType parseMonsterType(const std::string& str);
};
