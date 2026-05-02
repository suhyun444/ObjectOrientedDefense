#pragma once

#include "MonsterDescription.h"
#include <map>
#include <string>

class MonsterStatsLoader {
public:
    std::map<MonsterType, MonsterDescription> load(const std::string& statsFile);

private:
    MonsterType parseMonsterType(const std::string& str);
};
