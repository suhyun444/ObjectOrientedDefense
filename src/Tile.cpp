#include "Tile.h"
#include <iostream>

Tile::Tile(int gridX, int gridY)
    : GameObject(Tag::Tile),
      gridX(gridX),
      gridY(gridY),
      placedTower(nullptr) {

    const float tileSize = 50.f;
    position = {gridX * tileSize, gridY * tileSize};

    shape.setSize({tileSize - 24.f, tileSize - 24.f});
    shape.setPosition({gridX * tileSize + 12.f, gridY * tileSize + 12.f});
}

bool Tile::containsPoint(const sf::Vector2i& pixelPos) const {
    const float tileSize = 50.f;
    return pixelPos.x >= position.x && pixelPos.x < position.x + tileSize
        && pixelPos.y >= position.y && pixelPos.y < position.y + tileSize;
}

bool Tile::onClick() {
    if (!hasTower() && onBuildRequest) { onBuildRequest(this); return true; }
    if ( hasTower() && onTowerClick)  { onTowerClick(placedTower, this); return true; }
    return true;
}

void Tile::update() {}

void Tile::render(sf::RenderWindow& window) {
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color(46, 204, 113));
    shape.setOutlineThickness(10.f);
    window.draw(shape);

    if (highlighted) {
        sf::RectangleShape border(sf::Vector2f(48.f, 48.f));
        border.setPosition(position + sf::Vector2f(1.f, 1.f));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineThickness(2.f);
        border.setOutlineColor(sf::Color::Yellow);
        window.draw(border);
    }
}

RenderLayer Tile::getLayer() const {
    return RenderLayer::Background;
}
