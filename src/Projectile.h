#pragma once
#include "GameObject.h"
#include "ProjectileDescription.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

class Monster;

class Projectile : public GameObject {
private:
    ProjectileDescription description;
    bool alive;
    std::weak_ptr<Monster> target;

public:
    Projectile(const std::shared_ptr<Monster>& target, const ProjectileDescription& description = ProjectileDescription{});

    
    void update() override;
    bool isAlive() const override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
    
private:
    void attackMonster();
};
