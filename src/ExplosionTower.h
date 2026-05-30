#pragma once
#include "Tower.h"

class ExplosionTower : public Tower {
public:
    ExplosionTower();
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) override;
};
