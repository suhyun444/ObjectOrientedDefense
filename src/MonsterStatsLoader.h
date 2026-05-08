#pragma once

#include "MonsterStats.h"
#include <string>

class MonsterStatsLoader {
public:
    MonsterStats load(const std::string& statsFile);

private:
    MonsterType parseMonsterType(const std::string& str);
};
