#include "ExplosionProjectile.h"
#include "ExplosionEffect.h"
#include "Monster.h"
#include "ObjectFactory.h"
#include <cmath>

ExplosionProjectile::ExplosionProjectile(
    const std::shared_ptr<Monster>& target, int damage,
    std::function<std::vector<std::shared_ptr<Monster>>()> provider)
    : Projectile(target, damage, 200.f), monstersProvider(std::move(provider)) {}

void ExplosionProjectile::applyEffect(const std::shared_ptr<Monster>&) {

    if (monstersProvider) {
        for (const auto& m : monstersProvider()) {
            sf::Vector2f diff = m->getPosition() - position;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            if (dist <= RADIUS) m->takeDamage(damage);
        }
    }
    ObjectFactory::getInstance().registerEffect(std::make_shared<ExplosionEffect>(position));
}