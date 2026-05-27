#include "MostAdvancedTargeting.h"
#include "Monster.h"
#include <cmath>
#include <limits>

std::shared_ptr<Monster> MostAdvancedTargeting::selectTarget(
    sf::Vector2f origin, float range,
    const std::vector<std::shared_ptr<Monster>>& monsters) const
{
    std::shared_ptr<Monster> best;
    int bestWP = -1;
    float bestDist = std::numeric_limits<float>::max();
    for (const auto& m : monsters) {
        sf::Vector2f diff = m->getPosition() - origin;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist > range) continue;
        int wp = m->getWaypointIndex();
        float distToNext = m->getDistanceToNextWaypoint();
        if (wp > bestWP || (wp == bestWP && distToNext < bestDist)) {
            bestWP = wp;
            bestDist = distToNext;
            best = m;
        }
    }
    return best;
}
