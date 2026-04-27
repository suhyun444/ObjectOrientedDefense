#include "Map.h"
#include "ObjectFactory.h"
#include <SFML/Graphics/RectangleShape.hpp>

static const std::vector<sf::Vector2i> pathCoordinates = {
    {0,6}, {1,6}, {2,6}, {3,6},
    {4,6}, {5,6}, {6,6}, {7,6},
    {7,5}, {7,4}, {7,3}, {7,2}, {7,1},
    {8,1}, {9,1}, {10,1}, {11,1}, {12,1},
    {12,2}, {12,3}, {12,4}, {12,5}, {12,6}, {12,7}, {12,8},
    {11,8}, {10,8}, {9,8}, {8,8}, {7,8},
    {7,9}, {7,10}, {7,11}, {7,12}, {7,13},
    {8,13}, {9,13}, {10,13}, {11,13}, {12,13}, {13,13}, {14,13}, {15,13}, {16,13}, {17,13}, {18,13}, {19,13},
    {19,12}, {19,11}, {19,10}, {19,9}, {19,8},
    {18,8}, {17,8}, {16,8}, {15,8},
    {15,7}, {15,6}, {15,5}, {15,4}, {15,3},
    {16,3}, {17,3}, {18,3}, {19,3}, {20,3}, {21,3},
    {21,2}, {21,1}, {21,0}
};

// 타워를 배치할 수 있는 위치 (경로 주변)
static const std::vector<sf::Vector2i> buildableCoordinates = {
    {3,4}, {3,5},
    {5,4}, {6,4},
    {9,3}, {10,3}, {11,3},
    {10,6}, {11,6},
    {10,10}, {11,10}, {11,11},
    {17,5}, {17,6}, {18,5},
    {20,1}, {20,2},
};

Map::Map(int width, int height) : width(width), height(height) {}

void Map::initialize(ObjectFactory& factory) {
    path.setPathTiles(pathCoordinates);

    for (const auto& coord : buildableCoordinates) {
        auto tile = factory.createTile(coord.x, coord.y);
        tiles.push_back(tile);
    }
}

const Path& Map::getPath() const {
    return path;
}

std::shared_ptr<Tile> Map::getTile(int gridX, int gridY) const {
    for (const auto& tile : tiles) {
        if (!tile) continue;
        if (tile->getPosition().x == gridX * 50.f && tile->getPosition().y == gridY * 50.f) {
            return tile;
        }
    }
    return nullptr;
}

bool Map::canPlaceTower(int gridX, int gridY) const {
    auto tile = getTile(gridX, gridY);
    return tile && !tile->hasTower();
}

void Map::render(sf::RenderWindow& window) {
    const float tileSize = 50.f;
    sf::RectangleShape rect({tileSize - 2.f, tileSize - 2.f});
    rect.setFillColor(sf::Color(149, 165, 166));

    for (const auto& tilePos : path.getPathTiles()) {
        rect.setPosition({tilePos.x * tileSize, tilePos.y * tileSize});
        window.draw(rect);
    }
}

RenderLayer Map::getLayer() const {
    return RenderLayer::Background;
}
