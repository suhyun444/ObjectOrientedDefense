#pragma once

enum class ProjectileType {
    Normal,
    Slow,
    Explosion
};

struct ProjectileDescription {
    ProjectileType type = ProjectileType::Normal;
    float speed = 260.f;
    int damage = 10;
};
