#pragma once
#include "Tower.h"

class SniperTower : public Tower {
public:
    SniperTower();
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) override;
};
