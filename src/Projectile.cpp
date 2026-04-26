#include "Projectile.h"
#include "Monster.h"
#include "Time.h"
#include <cmath>

Projectile::Projectile(const std::shared_ptr<Monster>& target, const ProjectileDescription& description)
    : GameObject(Tag::Projectile), description(description), alive(true), target(target), shape(6.f) {
    shape.setFillColor(sf::Color(241, 196, 15));
    shape.setOrigin({6.f, 6.f});
    shape.setPosition(position);
}

void Projectile::attackMonster() {
    auto targetShared = target.lock();
    if (targetShared && targetShared->isAlive()) {
        targetShared->takeDamage(description.damage);
    }
}

void Projectile::onHit() {
    alive = false;
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
        onHit();
        return;
    }

    if (len > 0.001f) {
        dir /= len;
        position += dir * (description.speed * Time::getDeltaTime());
        shape.setPosition(position);
    }
}

bool Projectile::isAlive() const {
    return alive;
}

void Projectile::render(sf::RenderWindow& window) {
    window.draw(shape);
}

RenderLayer Projectile::getLayer() const {
    return RenderLayer::Projectile;
}
