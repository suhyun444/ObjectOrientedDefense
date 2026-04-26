#include "Monster.h"
#include "Player.h"
#include "Time.h"
#include <cmath>

Monster::Monster(const MonsterDescription& description)
        : GameObject(Tag::Monster),
            health(description.maxHealth),
            description(description),
            waypointIndex(0),
            alive(true),
            path(nullptr),
            targetPlayer(nullptr),
            shape(14.f) {
    shape.setFillColor(sf::Color(192, 57, 43));
    shape.setOrigin({14.f, 14.f});
    shape.setPosition(position);
}

void Monster::setPath(const Path* newPath) {
    path = newPath;
    waypointIndex = 0;
    if (path && path->size() > 0) {
        position = path->getPoint(0);
        shape.setPosition(position);
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

void Monster::dealDamageToPlayer() {
    if (targetPlayer) {
        targetPlayer->takeDamage(1);
    }
}

void Monster::moveAlongPath() {
    if (!path || path->size() == 0 || !alive) {
        return;
    }

    if (waypointIndex >= path->size()) {
        alive = false;
        return;
    }

    const sf::Vector2f target = path->getPoint(waypointIndex);
    sf::Vector2f dir = target - position;
    const float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len < 0.001f) {
        ++waypointIndex;
        if (waypointIndex >= path->size()) {
            alive = false;
        }
        return;
    }

    dir /= len;
    position += dir * (description.speed * Time::getDeltaTime());
    shape.setPosition(position);
}

void Monster::update() {
    moveAlongPath();
}

bool Monster::isAlive() const {
    return alive;
}

void Monster::render(sf::RenderWindow& window) {
    window.draw(shape);
}

RenderLayer Monster::getLayer() const {
    return RenderLayer::Entity;
}
