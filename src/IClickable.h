#pragma once
#include <SFML/System/Vector2.hpp>

class IClickable {
public:
    virtual ~IClickable() = default;

    virtual bool containsPoint(const sf::Vector2i& pixelPos) const = 0;
    virtual bool onClick() = 0;
    virtual bool isEnabled() const { return true; }
};
