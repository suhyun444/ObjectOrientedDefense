#pragma once
#include "ITargetingStrategy.h"

class MostAdvancedTargeting : public ITargetingStrategy {
public:
    std::shared_ptr<Monster> selectTarget(
        sf::Vector2f origin, float range,
        const std::vector<std::shared_ptr<Monster>>& monsters) const override;
};
