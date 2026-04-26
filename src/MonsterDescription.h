#pragma once

enum class MonsterType {
    Goblin,
    Skeleton,
    Wolf
};

struct MonsterDescription {
    MonsterType type = MonsterType::Goblin;
    int maxHealth = 100;
    float speed = 60.f;
    int rewardGold = 5;
};