#pragma once
#include "Tower.h"

class IceTower : public Tower {
public:
    IceTower();
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) override;
};
