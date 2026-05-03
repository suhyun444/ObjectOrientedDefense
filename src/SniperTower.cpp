#include "SniperTower.h"
#include "NormalProjectile.h"
#include "ObjectFactory.h"

SniperTower::SniperTower() {
    description = {
        TowerType::Sniper, 100, 30, 300.f, 0.5f, 10, 50, 3,
        sf::Color(34, 139, 34), "Sniper"
    };
}

std::shared_ptr<Monster> SniperTower::getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    return findMostAdvancedTarget(monsters);
}

void SniperTower::fire(const std::shared_ptr<Monster>& target) {
    createProjectile(target);
}

std::shared_ptr<Projectile> SniperTower::createProjectile(const std::shared_ptr<Monster>& target) {
    auto proj = std::make_shared<NormalProjectile>(target, description.damage, 400.f);
    proj->setPosition(position.x, position.y);
    ObjectFactory::getInstance().registerProjectile(proj);
    return proj;
}
