#pragma once
#include "GameObject.h"
#include "TowerDescription.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

class Monster;
class Projectile;

class Tower : public GameObject {
protected:
    TowerDescription description;
    int level;
    sf::Vector2i gridPosition;
    
public:
    Tower(const TowerDescription& description = TowerDescription{});
    virtual ~Tower() = default;
    
    void upgradeLevel();
    void setGridPosition(sf::Vector2i gridPosition);
    
    void update() override;
    bool isAlive() const override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;

private:
    virtual std::shared_ptr<Monster> getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const = 0;
    virtual void fire(const std::shared_ptr<Monster>& target) = 0;
    virtual std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target) = 0;
};
