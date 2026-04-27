#include "Tile.h"
#include <iostream>

Tile::Tile(int gridX, int gridY)
    : GameObject(Tag::Tile),
      gridX(gridX),
      gridY(gridY),
      tilePosition(0.f, 0.f),
      placedTower(nullptr) {

    const float tileSize = 50.f;
    position = {gridX * tileSize, gridY * tileSize};
    tilePosition = position;

    shape.setSize({tileSize - 2.f, tileSize - 2.f});
    shape.setPosition(position);
    shape.setFillColor(sf::Color(46, 204, 113));
}

bool Tile::containsPoint(const sf::Vector2i& pixelPos) const {
    const float tileSize = 50.f;
    return pixelPos.x >= tilePosition.x && pixelPos.x < tilePosition.x + tileSize
        && pixelPos.y >= tilePosition.y && pixelPos.y < tilePosition.y + tileSize;
}

bool Tile::onClick() {
    std::cout << "[Tile] clicked (" << gridX << ", " << gridY << ")\n";
    return true;
}

void Tile::update() {}

void Tile::render(sf::RenderWindow& window) {
    window.draw(shape);
}

RenderLayer Tile::getLayer() const {
    return RenderLayer::Background;
}
