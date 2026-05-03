#pragma once
#include "Tower.h"

class ExplosionTower : public Tower {
public:
    ExplosionTower();
    std::shared_ptr<Monster>    getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const override;
    void                        fire(const std::shared_ptr<Monster>& target) override;
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) override;
};
