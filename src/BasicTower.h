#pragma once
#include "Tower.h"

class BasicTower : public Tower {
public:
    BasicTower() = default;
    void fire(const std::shared_ptr<Monster>& target) override;
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) override;
};
