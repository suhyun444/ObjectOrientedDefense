#pragma once
#include "GameObject.h"
#include "TowerDescription.h"
#include "ITargetingStrategy.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>
#include <vector>

class Monster;
class Projectile;

class Tower : public GameObject {
protected:
    TowerDescription description;
    int level = 0;
    sf::Vector2i gridPosition;

private:
    bool alive = true;
    float fireCooldown = 0.f;
    sf::RectangleShape shape;
    std::unique_ptr<ITargetingStrategy> targetingStrategy;

public:
    std::function<std::vector<std::shared_ptr<Monster>>()> monstersProvider;
    Tower(const TowerDescription& desc = TowerDescription{});
    virtual ~Tower() = default;

    const TowerDescription& getDescription() const { return description; }
    int  getLevel()       const { return level; }
    int  getRefundGold()  const { return description.cost / 2; }
    bool isMaxLevel()     const { return level >= description.maxLevel - 1; }

    void upgrade();
    void kill();
    void setGridPosition(sf::Vector2i pos);
    void setMonstersProvider(std::function<std::vector<std::shared_ptr<Monster>>()> fn);

    void         update()                       override;
    bool         isAlive()                const override;
    void         render(sf::RenderWindow& win)  override;
    RenderLayer  getLayer()               const override;

protected:
    std::shared_ptr<Monster> selectTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const;

private:
    virtual std::shared_ptr<Monster>     getTarget(const std::vector<std::shared_ptr<Monster>>& monsters) const = 0;
    virtual void                         fire(const std::shared_ptr<Monster>& target) = 0;
    virtual std::shared_ptr<Projectile>  createProjectile(const std::shared_ptr<Monster>& target) = 0;
};
