#include "SniperTower.h"
#include "Projectile.h"

SniperTower::SniperTower() {
    description = {
        TowerType::Sniper, 100, 30, 300.f, 0.5f, 10, 50, 3,
        sf::Color(34, 139, 34), "Sniper"
    };
}

std::shared_ptr<Monster> SniperTower::getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    (void)monsters;
    return nullptr;
}

void SniperTower::fire(const std::shared_ptr<Monster>& target) {
    (void)target;
}

std::shared_ptr<Projectile> SniperTower::createProjectile(const std::shared_ptr<Monster>& target) {
    (void)target;
    return nullptr;
}
