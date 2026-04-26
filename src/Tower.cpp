#include "Tower.h"
#include "Monster.h"
#include "Time.h"
#include <cmath>

Tower::Tower(const TowerDescription& description)
    : GameObject(Tag::Tower),
    description(description),
      fireCooldown(0.f),
      level(0),
    gridPosition(0, 0),
      alive(true),
      shape(18.f) {
    shape.setFillColor(sf::Color(52, 152, 219));
    shape.setOrigin({18.f, 18.f});
    shape.setPosition(position);
}

void Tower::upgradeLevel() {
    ++level;
}

int Tower::getAttackDamage() const {
    return description.damage + level * description.damagePerLevel;
}

void Tower::setGridPosition(int gridX, int gridY) {
    gridPosition = {gridX, gridY};
}

sf::Vector2i Tower::getGridPosition() const {
    return gridPosition;
}

std::shared_ptr<Monster> Tower::acquireTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const {
    for (const auto& monster : monsters) {
        if (!monster || !monster->isAlive()) {
            continue;
        }

        const sf::Vector2f mPos = monster->getPosition();
        const sf::Vector2f delta = mPos - position;
        const float dist2 = delta.x * delta.x + delta.y * delta.y;
        if (dist2 <= description.range * description.range) {
            return monster;
        }
    }
    return nullptr;
}

void Tower::update() {
    if (fireCooldown > 0.f) {
        fireCooldown -= Time::getDeltaTime();
    }
}

bool Tower::isAlive() const {
    return alive;
}

void Tower::render(sf::RenderWindow& window) {
    shape.setPosition(position);
    window.draw(shape);
}

RenderLayer Tower::getLayer() const {
    return RenderLayer::Entity;
}
