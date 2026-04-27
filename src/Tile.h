#pragma once
#include "GameObject.h"
#include "IClickable.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Tower;

class Tile : public GameObject, public IClickable {
private:
    sf::RectangleShape shape;
    int gridX;
    int gridY;
    sf::Vector2f tilePosition;
    Tower* placedTower;

public:
    Tile(int gridX, int gridY);

    sf::Vector2f getTilePosition() const { return tilePosition; }
    void setTower(Tower* tower) { placedTower = tower; }
    Tower* getTower() const { return placedTower; }
    bool hasTower() const { return placedTower != nullptr; }

    bool containsPoint(const sf::Vector2i& pixelPos) const override;
    bool onClick() override;
    bool isEnabled() const override { return true; }

    void update() override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};
