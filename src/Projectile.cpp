#include "Projectile.h"
#include "Monster.h"
#include "Time.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

Projectile::Projectile(const std::shared_ptr<Monster>& target, int damage, float speed)
    : GameObject(Tag::Projectile), damage(damage), speed(speed), alive(true), target(target) {}

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
        applyEffect(targetShared);
        alive = false;
        return;
    }

    if (len > 0.001f) {
        dir /= len;
        position += dir * (speed * Time::getDeltaTime());
    }
}

bool Projectile::isAlive() const {
    return alive;
}

void Projectile::render(sf::RenderWindow& window) {
    sf::CircleShape circle(5.f);
    circle.setFillColor(getColor());
    circle.setOrigin(5.f, 5.f);
    circle.setPosition(position);
    window.draw(circle);
}

RenderLayer Projectile::getLayer() const {
    return RenderLayer::Projectile;
}
