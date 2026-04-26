#include "BasicTower.h"
#include "Projectile.h"

void BasicTower::fire(const std::shared_ptr<Monster>& target) {
    (void)target;
    // Intentionally left blank for initial implementation stage.
}

std::shared_ptr<Projectile> BasicTower::createProjectile(const std::shared_ptr<Monster>& target) {
    (void)target;
    return nullptr;
}
