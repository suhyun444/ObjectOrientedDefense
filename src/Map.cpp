#include "Map.h"
#include "ObjectFactory.h"

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
    {3,5},{3,7},{4,7},{6,4},{6,5},{8,5},{8,2},{8,9},{8,12},
    {10,10},{11,2},{11,4},{11,5},{11,10},{13,4},{13,7},{16,4},{16,7},
    {16,10},{16,11},{17,4},{18,9},{18,12},{20,2}
};

Map::Map(int width, int height) : width(width), height(height) {
    initialize();
}

void Map::initialize() {
    path = ObjectFactory::getInstance().createPath(pathCoordinates);

    for (const auto& coord : buildableCoordinates) {
        auto tile = ObjectFactory::getInstance().createTile(coord.x, coord.y);
        tiles.push_back(tile);
    }
}

const Path& Map::getPath() const {
    return *path;
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

