#pragma once
#include "GameObject.h"
#include "MonsterDescription.h"
#include "Path.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>

class Player;

class Monster : public GameObject {
private:
    int health;
    MonsterDescription description;
    sf::Vector2f position;
    bool alive;
    const Path* path;
    Player* targetPlayer;

public:
    explicit Monster(const MonsterDescription& description = MonsterDescription{});

    void setPath(const Path* newPath);
    void setTargetPlayer(Player* player);
    void takeDamage(int damage);
    void attackPlayer();

    void update() override;
    bool isAlive() const override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};
