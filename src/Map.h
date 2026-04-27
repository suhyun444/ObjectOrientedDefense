#pragma once
#include <memory>
#include <vector>
#include "Path.h"
#include "Tile.h"
#include "IRenderable.h"

class ObjectFactory;

class Map : public IRenderable {
private:
    int width;
    int height;
    Path path;
    std::vector<std::shared_ptr<Tile>> tiles;

public:
    Map(int width, int height);
    void initialize(ObjectFactory& factory);

    const Path& getPath() const;
    std::shared_ptr<Tile> getTile(int gridX, int gridY) const;
    bool canPlaceTower(int gridX, int gridY) const;

    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};
