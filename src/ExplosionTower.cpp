#include "ExplosionTower.h"
#include "Projectile.h"

ExplosionTower::ExplosionTower() {
    description = {
        TowerType::Explosion, 125, 20, 140.f, 0.8f, 8, 60, 3,
        sf::Color(220, 100, 30), "Explosion"
    };
}

std::shared_ptr<Monster> ExplosionTower::getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    (void)monsters;
    return nullptr;
}

void ExplosionTower::fire(const std::shared_ptr<Monster>& target) {
    (void)target;
}

std::shared_ptr<Projectile> ExplosionTower::createProjectile(const std::shared_ptr<Monster>& target) {
    (void)target;
    return nullptr;
}
