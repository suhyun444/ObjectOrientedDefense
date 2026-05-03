#include "NormalProjectile.h"
#include "Monster.h"

NormalProjectile::NormalProjectile(const std::shared_ptr<Monster>& target, int damage, float speed)
    : Projectile(target, damage, speed) {}

void NormalProjectile::applyEffect(const std::shared_ptr<Monster>& t) {
    t->takeDamage(damage);
}
