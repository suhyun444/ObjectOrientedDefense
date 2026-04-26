#pragma once

enum class TowerType {
    Basic,
    Ice,
    Sniper,
    Explosion
};

struct TowerDescription {
    TowerType type = TowerType::Basic;
    int cost = 50;
    int damage = 10;
    float range = 170.f;
    float fireRate = 1.25f;
    int damagePerLevel = 5;
};
