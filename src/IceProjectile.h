#pragma once
#include "Projectile.h"

class IceProjectile : public Projectile {
public:
    IceProjectile(const std::shared_ptr<Monster>& target, int damage);
protected:
    void applyEffect(const std::shared_ptr<Monster>& t) override;
    sf::Color getColor() const override { return sf::Color::Cyan; }
};
