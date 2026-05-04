#include "IceProjectile.h"
#include "Monster.h"

IceProjectile::IceProjectile(const std::shared_ptr<Monster>& target, int damage)
    : Projectile(target, damage, 260.f) {}

void IceProjectile::applyEffect(const std::shared_ptr<Monster>& t) {
    t->takeDamage(damage);
    t->applySlow(0.5f, 2.0f);
}
