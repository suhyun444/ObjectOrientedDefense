#include "Monster.h"
#include "Time.h"
#include <cmath>

Monster::Monster(const MonsterDescription& description)
    : GameObject(Tag::Monster),
      health(description.maxHealth),
      description(description),
      alive(true),
      path(nullptr),
      waypointIndex(0) {
    const float radius = 15.f;
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    if (description.hollow) {
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(description.color);
        shape.setOutlineThickness(2.f);
    } else {
        shape.setFillColor(description.color);
    }
}

void Monster::setPath(const Path* newPath) {
    path = newPath;
    if (path && path->size() > 0) {
        position = path->getPoint(0);
    }
}

void Monster::setOnReachedEnd(std::function<void()> callback) {
    onReachedEnd = std::move(callback);
}

void Monster::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        alive = false;
    }
}

void Monster::update() {
    if (!alive) return;
    moveAlongPath();
}

bool Monster::isAlive() const {
    return alive;
}

void Monster::render(sf::RenderWindow& window) {
    if (!alive) return;
    shape.setPosition(position);
    window.draw(shape);
}

RenderLayer Monster::getLayer() const {
    return RenderLayer::Entity;
}

void Monster::moveAlongPath() {
    if (!path || waypointIndex >= path->size() - 1) {
        if (onReachedEnd) onReachedEnd();
        alive = false;
        return;
    }
    sf::Vector2f target = path->getNextPoint(waypointIndex);
    sf::Vector2f dir    = target - position;
    float dist = std::hypot(dir.x, dir.y);
    float step = description.speed * Time::getDeltaTime();

    if (dist <= step) {
        position = target;
        ++waypointIndex;
        if (waypointIndex >= path->size() - 1) {
            if (onReachedEnd) onReachedEnd();
            alive = false;
            return;
        }
    } else {
        position += (dir / dist) * step;
    }
}
