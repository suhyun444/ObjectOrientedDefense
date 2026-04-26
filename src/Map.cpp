#include "Map.h"

Map::Map(int width, int height) : width(width), height(height) {
    buildDefaultPath();
}

void Map::addTile(const std::shared_ptr<Tile>& tile) {
    tiles.push_back(tile);
}

std::shared_ptr<Tile> Map::getTile(int gridX, int gridY) const {
    for (const auto& tile : tiles) {
        if (!tile) {
            continue;
        }
        if (tile->getPosition().x == gridX * 50.f && tile->getPosition().y == gridY * 50.f) {
            return tile;
        }
    }
    return nullptr;
}

bool Map::canPlaceTower(int gridX, int gridY) const {
    auto tile = getTile(gridX, gridY);
    if (!tile) {
        return true;
    }
    return tile->getType() == TileType::Buildable;
}

const Path& Map::getPath() const {
    return path;
}

void Map::buildDefaultPath() {
    const float tileSize = 50.f;
    std::vector<sf::Vector2f> defaultPoints = {
        {0.f * tileSize, 6.f * tileSize},
        {4.f * tileSize, 6.f * tileSize},
        {4.f * tileSize, 2.f * tileSize},
        {8.f * tileSize, 2.f * tileSize},
        {8.f * tileSize, 8.f * tileSize}
    };
    path.setPoints(defaultPoints);
}
