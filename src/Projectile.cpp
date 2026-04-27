#include "Projectile.h"
#include "Monster.h"
#include "Time.h"
#include <cmath>

Projectile::Projectile(const std::shared_ptr<Monster>& target, const ProjectileDescription& description)
    : GameObject(Tag::Projectile), description(description), alive(true), target(target) {}

void Projectile::attackMonster() {
    auto targetShared = target.lock();
    if (targetShared && targetShared->isAlive()) {
        targetShared->takeDamage(description.damage);
    }
}

void Projectile::update() {
    auto targetShared = target.lock();
    if (!targetShared || !targetShared->isAlive()) {
        alive = false;
        return;
    }

    const sf::Vector2f targetPos = targetShared->getPosition();
    sf::Vector2f dir = targetPos - position;
    const float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len < 8.f) {
        attackMonster();
        alive = false;
        return;
    }

    if (len > 0.001f) {
        dir /= len;
        position += dir * (description.speed * Time::getDeltaTime());
    }
}

bool Projectile::isAlive() const {
    return alive;
}

void Projectile::render(sf::RenderWindow& window) {}

RenderLayer Projectile::getLayer() const {
    return RenderLayer::Projectile;
}
