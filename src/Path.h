#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cstddef>

class Path {
private:
    std::vector<sf::Vector2f> points;

public:
    Path() = default;
    explicit Path(const std::vector<sf::Vector2f>& points);

    void setPoints(const std::vector<sf::Vector2f>& points);
    const std::vector<sf::Vector2f>& getPoints() const;

    int size() const;
    const sf::Vector2f& getPoint(int index) const;
    sf::Vector2f getNextPoint(int index) const;
};
