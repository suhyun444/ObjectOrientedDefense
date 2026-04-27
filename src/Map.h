#pragma once
#include <memory>
#include <vector>
#include "Path.h"
#include "Tile.h"

class ObjectFactory;

class Map {
private:
    int width;
    int height;
    std::shared_ptr<Path> m_path;
    std::vector<std::shared_ptr<Tile>> tiles;

public:
    Map(int width, int height);

    const Path& getPath() const;
    std::shared_ptr<Tile> getTile(int gridX, int gridY) const;
    bool canPlaceTower(int gridX, int gridY) const;

private:
    void initialize();
};
