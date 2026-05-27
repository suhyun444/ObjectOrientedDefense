#pragma once
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

class Monster;

class ITargetingStrategy {
public:
    virtual ~ITargetingStrategy() = default;
    virtual std::shared_ptr<Monster> selectTarget(
        sf::Vector2f origin, float range,
        const std::vector<std::shared_ptr<Monster>>& monsters) const = 0;
};
