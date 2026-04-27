#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "IRenderable.h"

class Path : public IRenderable {
private:
    std::vector<sf::Vector2i> pathTiles;
    std::vector<sf::Vector2f> waypoints;
    std::vector<sf::RectangleShape> m_shapes;

public:
    Path() = default;

    void setPathTiles(const std::vector<sf::Vector2i>& tiles);
    const std::vector<sf::Vector2i>& getPathTiles() const;

    int size() const;
    const sf::Vector2f& getPoint(int index) const;
    sf::Vector2f getNextPoint(int index) const;

    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};
