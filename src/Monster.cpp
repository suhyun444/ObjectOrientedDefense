#include "Monster.h"
#include "Player.h"
#include "Time.h"
#include <cmath>

Monster::Monster(const MonsterDescription& description)
    : GameObject(Tag::Monster),
      health(description.maxHealth),
      description(description),
      alive(true),
      path(nullptr),
      targetPlayer(nullptr),
      waypointIndex(0) {
}

void Monster::setPath(const Path* newPath) {
    path = newPath;
    if (path && path->size() > 0) {
        position = path->getPoint(0);
    }
}

void Monster::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        alive = false;
    }
}

void Monster::setTargetPlayer(Player* player) {
    targetPlayer = player;
}


void Monster::update() {}

bool Monster::isAlive() const {
    return alive;
}

void Monster::render(sf::RenderWindow& window) {}

    RenderLayer Monster::getLayer() const {
    return RenderLayer::Entity;
}
