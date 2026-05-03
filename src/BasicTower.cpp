#include "BasicTower.h"
#include "Projectile.h"

BasicTower::BasicTower() {
    description = {
        TowerType::Basic, 50, 10, 170.f, 1.25f, 5, 30, 3,
        sf::Color(70, 130, 180), "Basic"
    };
}

std::shared_ptr<Monster> BasicTower::getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    (void)monsters;
    return nullptr;
}

void BasicTower::fire(const std::shared_ptr<Monster>& target) {
    (void)target;
}

std::shared_ptr<Projectile> BasicTower::createProjectile(const std::shared_ptr<Monster>& target) {
    (void)target;
    return nullptr;
}
