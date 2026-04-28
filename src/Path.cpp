#include "Path.h"

void Path::setPathTiles(const std::vector<sf::Vector2i>& tiles) {
    pathTiles = tiles;
    waypoints.clear();

    if (tiles.empty()) return;

    const float tileSize = 50.f;

    waypoints.push_back({tiles[0].x * tileSize, tiles[0].y * tileSize});

    for (int i = 1; i < static_cast<int>(tiles.size()) - 1; i++) {
        int dx1 = tiles[i].x - tiles[i - 1].x;
        int dy1 = tiles[i].y - tiles[i - 1].y;
        int dx2 = tiles[i + 1].x - tiles[i].x;
        int dy2 = tiles[i + 1].y - tiles[i].y;

        if (dx1 != dx2 || dy1 != dy2) {
            waypoints.push_back({tiles[i].x * tileSize, tiles[i].y * tileSize});
        }
    }

    waypoints.push_back({tiles.back().x * tileSize, tiles.back().y * tileSize});

    shapes.clear();
    for (const auto& coord : tiles) {
        sf::RectangleShape rect({tileSize - 2.f, tileSize - 2.f});
        rect.setFillColor(sf::Color(149, 165, 166));
        rect.setPosition({coord.x * tileSize, coord.y * tileSize});
        shapes.push_back(rect);
    }
}

const std::vector<sf::Vector2i>& Path::getPathTiles() const {
    return pathTiles;
}

int Path::size() const {
    return static_cast<int>(waypoints.size());
}

const sf::Vector2f& Path::getPoint(int index) const {
    static const sf::Vector2f kOrigin(0.f, 0.f);
    if (index < 0 || index >= static_cast<int>(waypoints.size())) {
        return kOrigin;
    }
    return waypoints[index];
}

sf::Vector2f Path::getNextPoint(int index) const {
    if (waypoints.empty()) return {0.f, 0.f};
    if (index + 1 >= static_cast<int>(waypoints.size())) return waypoints.back();
    return waypoints[index + 1];
}

void Path::render(sf::RenderWindow& window) {
    for (const auto& shape : shapes)
        window.draw(shape);
}

RenderLayer Path::getLayer() const {
    return RenderLayer::Background;
}
