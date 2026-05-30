#include "IceTower.h"
#include "IceProjectile.h"
#include "ObjectFactory.h"
#include "StrongestTargeting.h"

IceTower::IceTower() {
    description = {
        TowerType::Ice, 75, 8, 150.f, 1.0f, 4, 40, 3,
        sf::Color(0, 200, 220), "Ice"
    };
    setTargetingStrategy(std::make_unique<StrongestTargeting>());
}

std::shared_ptr<Projectile> IceTower::createProjectile(const std::shared_ptr<Monster>& target) {
    auto proj = std::make_shared<IceProjectile>(target, description.damage);
    proj->setPosition(position.x + 23.f, position.y + 23.f);
    ObjectFactory::getInstance().registerProjectile(proj);
    return proj;
}
