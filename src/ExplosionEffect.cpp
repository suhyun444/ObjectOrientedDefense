#include "ExplosionEffect.h"
#include "Time.h"
#include <SFML/Graphics/CircleShape.hpp>

ExplosionEffect::ExplosionEffect(sf::Vector2f pos)
    : GameObject(Tag::Default) {
    position = pos;
}

void ExplosionEffect::update() {
    elapsed += Time::getDeltaTime();
}

bool ExplosionEffect::isAlive() const {
    return elapsed < DURATION;
}

void ExplosionEffect::render(sf::RenderWindow& window) {
    float t = elapsed / DURATION;
    float r = MAX_RADIUS * t;
    sf::Uint8 a = static_cast<sf::Uint8>(255 * (1.f - t));

    sf::CircleShape circle(r);
    circle.setOrigin(r, r);
    circle.setFillColor(sf::Color(255, 100, 0, a));
    circle.setPosition(position);
    window.draw(circle);
}

RenderLayer ExplosionEffect::getLayer() const {
    return RenderLayer::Projectile;
}
