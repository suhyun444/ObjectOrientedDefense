#pragma once
#include "Projectile.h"

class NormalProjectile : public Projectile {
public:
    NormalProjectile(const std::shared_ptr<Monster>& target, int damage, float speed = 260.f);
protected:
    void applyEffect(const std::shared_ptr<Monster>& t) override;
    sf::Color getColor() const override { return sf::Color::Yellow; }
};
