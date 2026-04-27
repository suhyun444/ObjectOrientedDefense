#include "Tower.h"
#include "Monster.h"

Tower::Tower(const TowerDescription& description)
    : GameObject(Tag::Tower),
      description(description),
      level(0),
      gridPosition(0, 0) {}

void Tower::upgradeLevel() {
    ++level;
}

void Tower::setGridPosition(sf::Vector2i pos) {
    gridPosition = pos;
}

void Tower::update() {}

bool Tower::isAlive() const {
    return true;
}

void Tower::render(sf::RenderWindow& window) {}

RenderLayer Tower::getLayer() const {
    return RenderLayer::Entity;
}
