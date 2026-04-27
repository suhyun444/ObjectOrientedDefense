#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class Path {
private:
    std::vector<sf::Vector2i> pathTiles;
    std::vector<sf::Vector2f> waypoints;

public:
    Path() = default;

    void setPathTiles(const std::vector<sf::Vector2i>& tiles);
    const std::vector<sf::Vector2i>& getPathTiles() const;

    int size() const;
    const sf::Vector2f& getPoint(int index) const;
    sf::Vector2f getNextPoint(int index) const;
};
