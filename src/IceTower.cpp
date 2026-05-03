#include "IceTower.h"
#include "Projectile.h"

IceTower::IceTower() {
    description = {
        TowerType::Ice, 75, 8, 150.f, 1.0f, 4, 40, 3,
        sf::Color(0, 200, 220), "Ice"
    };
}

std::shared_ptr<Monster> IceTower::getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    (void)monsters;
    return nullptr;
}

void IceTower::fire(const std::shared_ptr<Monster>& target) {
    (void)target;
}

std::shared_ptr<Projectile> IceTower::createProjectile(const std::shared_ptr<Monster>& target) {
    (void)target;
    return nullptr;
}
