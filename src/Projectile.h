#pragma once
#include "GameObject.h"
#include <SFML/Graphics/Color.hpp>
#include <memory>

class Monster;

class Projectile : public GameObject {
protected:
    int damage;
private:
    float speed;
    bool alive = true;
    std::weak_ptr<Monster> target;

public:
    Projectile(const std::shared_ptr<Monster>& target, int damage, float speed);
    virtual ~Projectile() = default;

    void update() override;
    bool isAlive() const override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;

protected:
    virtual void applyEffect(const std::shared_ptr<Monster>& t) = 0;
    virtual sf::Color getColor() const = 0;
};
