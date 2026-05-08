#pragma once

#include "MonsterDescription.h"
#include <map>

class MonsterStats {
public:
    MonsterStats() = default;
    explicit MonsterStats(std::map<MonsterType, MonsterDescription> data);
    MonsterDescription get(MonsterType type) const;

private:
    std::map<MonsterType, MonsterDescription> data;
};
