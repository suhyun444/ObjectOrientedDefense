#include "StrongestTargeting.h"
#include "Monster.h"
#include <cmath>

std::shared_ptr<Monster> StrongestTargeting::selectTarget(
    sf::Vector2f origin, float range,
    const std::vector<std::shared_ptr<Monster>>& monsters) const
{
    std::shared_ptr<Monster> best;
    int bestHp = -1;
    for (const auto& m : monsters) {
        sf::Vector2f diff = m->getPosition() - origin;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist > range) continue;
        int hp = m->getHealth();
        if (hp > bestHp) {
            bestHp = hp;
            best = m;
        }
    }
    return best;
}
