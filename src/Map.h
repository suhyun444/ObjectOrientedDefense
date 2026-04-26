#pragma once
#include <memory>
#include <vector>
#include "Path.h"
#include "Tile.h"

class Map {
private:
    int width;
    int height;
    std::vector<std::shared_ptr<Tile>> tiles;
    Path path;

public:
    Map(int width, int height);

    const Path& getPath() const;
};
