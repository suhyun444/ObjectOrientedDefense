#include "MonsterStats.h"

MonsterStats::MonsterStats(std::map<MonsterType, MonsterDescription> data)
    : data(std::move(data)) {}

MonsterDescription MonsterStats::get(MonsterType type) const {
    auto it = data.find(type);
    if (it != data.end()) return it->second;
    return MonsterDescription{};
}
