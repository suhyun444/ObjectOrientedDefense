#pragma once
#include "Projectile.h"
#include <functional>
#include <vector>

class ExplosionProjectile : public Projectile {
    std::function<std::vector<std::shared_ptr<Monster>>()> monstersProvider;
    static constexpr float RADIUS = 80.f;
public:
    ExplosionProjectile(const std::shared_ptr<Monster>& target, int damage,
                        std::function<std::vector<std::shared_ptr<Monster>>()> provider);
protected:
    void applyEffect(const std::shared_ptr<Monster>& t) override;
    sf::Color getColor() const override { return sf::Color(255, 100, 0); }
};
