#include "BasicTower.h"
#include "NormalProjectile.h"
#include "ObjectFactory.h"

BasicTower::BasicTower() {
    description = {
        TowerType::Basic, 50, 10, 170.f, 1.25f, 5, 30, 3,
        sf::Color(70, 130, 180), "Basic"
    };
}

std::shared_ptr<Monster> BasicTower::getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    return selectTarget(monsters);
}

void BasicTower::fire(const std::shared_ptr<Monster>& target) {
    createProjectile(target);
}

std::shared_ptr<Projectile> BasicTower::createProjectile(const std::shared_ptr<Monster>& target) {
    auto proj = std::make_shared<NormalProjectile>(target, description.damage,400.f);
    proj->setPosition(position.x + 23.f, position.y + 23.f);
    ObjectFactory::getInstance().registerProjectile(proj);
    return proj;
}
