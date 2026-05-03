#pragma once
#include "GameObject.h"
#include "IClickable.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

class Tower;

class Tile : public GameObject, public IClickable {
private:
    sf::RectangleShape shape;
    int gridX;
    int gridY;
    Tower* placedTower;
    bool highlighted = false;

public:
    std::function<void(Tile*)>         onBuildRequest;
    std::function<void(Tower*, Tile*)> onTowerClick;

    Tile(int gridX, int gridY);

    sf::Vector2f getPosition() const { return position; }
    int getGridX() const { return gridX; }
    int getGridY() const { return gridY; }

    void setTower(Tower* tower) { placedTower = tower; }
    Tower* getTower() const { return placedTower; }
    bool hasTower() const { return placedTower != nullptr; }

    void setHighlighted(bool h) { highlighted = h; }

    bool containsPoint(const sf::Vector2i& pixelPos) const override;
    bool onClick() override;
    bool isEnabled() const override { return true; }

    void update() override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};
