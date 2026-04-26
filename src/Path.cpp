#include "Path.h"

Path::Path(const std::vector<sf::Vector2f>& positions) : positions(positions) {}

void Path::setPositions(const std::vector<sf::Vector2f>& newPositions) {
    positions = newPositions;
}

const std::vector<sf::Vector2f>& Path::getPositions() const {
    return positions;
}

void Path::setPoints(const std::vector<sf::Vector2f>& newPoints) {
    setPositions(newPoints);
}

const std::vector<sf::Vector2f>& Path::getPoints() const {
    return getPositions();
}

std::size_t Path::size() const {
    return positions.size();
}

const sf::Vector2f& Path::getPoint(std::size_t index) const {
    static const sf::Vector2f kOrigin(0.f, 0.f);
    if (index >= positions.size()) {
        return kOrigin;
    }
    return positions[index];
}

sf::Vector2f Path::getNextPoint(std::size_t index) const {
    if (positions.empty()) {
        return {0.f, 0.f};
    }
    if (index + 1 >= positions.size()) {
        return positions.back();
    }
    return positions[index + 1];
}
