#pragma once
#include "GameObject.h"
#include "MonsterDescription.h"
#include "Path.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>

class Monster : public GameObject {
private:
    int health;
    MonsterDescription description;
    bool alive;
    const Path* path;
    std::function<void()> onReachedEnd;
    int waypointIndex;
    sf::CircleShape shape;
    float slowTimer = 0.f;
    float speedMultiplier = 1.f;

public:
    explicit Monster(const MonsterDescription& description = MonsterDescription{});

    void setPath(const Path* newPath);
    void setOnReachedEnd(std::function<void()> callback);
    void takeDamage(int damage);
    void applySlow(float factor, float duration);
    int getWaypointIndex() const { return waypointIndex; }

    void update() override;
    bool isAlive() const override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
private:
    void moveAlongPath();
};
