#include "Map.h"

Map::Map(int width, int height) : width(width), height(height) {}

const Path& Map::getPath() const {
    return path;
}
