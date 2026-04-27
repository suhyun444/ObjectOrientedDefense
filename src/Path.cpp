#include "Path.h"

Path::Path(const std::vector<sf::Vector2f>& points) : points(points) {}

void Path::setPoints(const std::vector<sf::Vector2f>& newPoints) {
    points = newPoints;
}

const std::vector<sf::Vector2f>& Path::getPoints() const {
    return points;
}

int Path::size() const {
    return static_cast<int>(points.size());
}

const sf::Vector2f& Path::getPoint(int index) const {
    static const sf::Vector2f kOrigin(0.f, 0.f);
    if (index < 0 || index >= static_cast<int>(points.size())) {
        return kOrigin;
    }
    return points[index];
}

sf::Vector2f Path::getNextPoint(int index) const {
    if (points.empty()) {
        return {0.f, 0.f};
    }
    if (index + 1 >= static_cast<int>(points.size())) {
        return points.back();
    }
    return points[index + 1];
}
