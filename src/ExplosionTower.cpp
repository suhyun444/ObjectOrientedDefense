#include "ExplosionTower.h"
#include "ExplosionProjectile.h"
#include "ObjectFactory.h"

ExplosionTower::ExplosionTower() {
    description = {
        TowerType::Explosion, 125, 20, 140.f, 0.8f, 8, 60, 3,
        sf::Color(220, 100, 30), "Explosion"
    };
}

std::shared_ptr<Projectile> ExplosionTower::createProjectile(const std::shared_ptr<Monster>& target) {
    auto proj = std::make_shared<ExplosionProjectile>(target, description.damage, monstersProvider);
    proj->setPosition(position.x + 23.f, position.y + 23.f);
    ObjectFactory::getInstance().registerProjectile(proj);
    return proj;
}
