#include "Wave.h"
#include "Monster.h"
#include "ObjectFactory.h"
#include "Time.h"
#include <iostream>

static const char* monsterTypeName(MonsterType t) {
    switch (t) {
        case MonsterType::Goblin:   return "Goblin";
        case MonsterType::Skeleton: return "Skeleton";
        case MonsterType::Wolf:     return "Wolf";
    }
    return "Unknown";
}

Wave::Wave(const Path* path)
    : level(0),
      spawnIndex(0),
      spawningComplete(true),
      spawnElapsed(0.f),
      path(path) {
    monsterStats = parser.parseMonsterStats("data/monster_stats.csv");
    waveStartButton = ObjectFactory::getInstance().createWaveStartButton(this);
}

bool Wave::loadFromFile() {
    ++level;
    spawnIndex = 0;
    spawnElapsed = 0.f;
    monsters.clear();
    std::string filePath = "data/wave_" + std::to_string(level) + ".csv";
    description = parser.parseWave(filePath);

    if (description.spawns.empty()) {
        std::cerr << "[Wave " << level << "] 파일 로딩 실패: " << filePath << "\n";
        std::cout << "!!!!!VICTORY!!!!!! CALL GAMEMANAGER";
        return false;
    }
    spawningComplete = false;

    // 첫 스폰을 즉시 트리거하기 위해 elapsed를 첫 spawnTime으로 초기화
    spawnElapsed = description.spawns[0].spawnTime;
    std::cout << "[Wave " << level << "] Start\n";
    return true;
}

int Wave::GetLevel() const {
    return level;
}

void Wave::spawnMonster() {
    const SpawnEvent& ev = description.spawns[spawnIndex];

    MonsterDescription desc;
    auto it = monsterStats.find(ev.type);
    if (it != monsterStats.end()) desc = it->second;

    auto monster = ObjectFactory::getInstance().createMonster(path, desc);
    monsters.push_back(monster);

    std::cout << "[Wave " << level << "] Spawn : " << monsterTypeName(ev.type)
              << " (" << (spawnIndex + 1) << "/" << description.spawns.size() << ")\n";

    ++spawnIndex;
    if (spawnIndex >= static_cast<int>(description.spawns.size())) {
        spawningComplete = true;
        std::cout << "[Wave " << level << "] All Monster Spawn Complete\n";
    }
}

bool Wave::isAllMonstersDefeated() const {
    for (const auto& m : monsters) {
        if (m->isAlive()) return false;
    }
    return true;
}

bool Wave::isComplete() const {
    return spawningComplete && isAllMonstersDefeated();
}

void Wave::update() {
    if (spawningComplete) return;

    spawnElapsed += Time::getDeltaTime();

    float interval = description.spawns[spawnIndex].spawnTime;
    if (spawnElapsed >= interval) {
        spawnMonster();
        spawnElapsed = 0.f;
    }
}

bool Wave::isAlive() const {
    return true;
}
