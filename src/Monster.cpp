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

void Monster::setOnDefeated(std::function<void()> callback) {
    onDefeated = std::move(callback);
}

void Monster::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        alive = false;
        if (onDefeated) onDefeated();
    }
}

void Monster::applySlow(float factor, float duration) {
    speedMultiplier = factor;
    slowTimer = duration;
}

float Monster::getDistanceToNextWaypoint() const {
    if (!path) return 0.f;
    sf::Vector2f diff = path->getNextPoint(waypointIndex) - position;
    return std::hypot(diff.x, diff.y);
}

void Monster::update() {
    if (!alive) return;
    if (slowTimer > 0.f) {
        slowTimer -= Time::getDeltaTime();
        if (slowTimer <= 0.f) speedMultiplier = 1.f;
    }
    moveAlongPath();
}

bool Monster::isAlive() const {
    return alive;
}

void Monster::render(sf::RenderWindow& window) {
    if (!alive) return;

    sf::Color base = description.color;
    if (slowTimer > 0.f) {
        base = sf::Color(
            static_cast<sf::Uint8>((base.r + 100) / 2),
            static_cast<sf::Uint8>((base.g + 180) / 2),
            static_cast<sf::Uint8>((base.b + 255) / 2)
        );
    }

    if (description.hollow)
        shape.setOutlineColor(base);
    else
        shape.setFillColor(base);

    shape.setPosition(position);
    window.draw(shape);

    float ratio = static_cast<float>(health) / description.maxHealth;
    sf::Color barColor = ratio > 0.66f ? sf::Color(80, 200, 80)
                       : ratio > 0.33f ? sf::Color(220, 200, 50)
                                       : sf::Color(220, 60, 60);

    sf::RectangleShape bgBar({30.f, 4.f});
    bgBar.setFillColor(sf::Color(60, 60, 60));
    bgBar.setPosition(position.x - 15.f, position.y - 21.f);
    window.draw(bgBar);

    sf::RectangleShape hpBar({30.f * ratio, 4.f});
    hpBar.setFillColor(barColor);
    hpBar.setPosition(position.x - 15.f, position.y - 21.f);
    window.draw(hpBar);
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
    float step = description.speed * speedMultiplier * Time::getDeltaTime();

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
