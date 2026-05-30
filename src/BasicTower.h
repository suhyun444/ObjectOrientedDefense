#pragma once
#include "Tower.h"

class BasicTower : public Tower {
public:
    BasicTower();
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) override;
};
