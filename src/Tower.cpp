#include "Tower.h"
#include "Monster.h"

static sf::Font& getSharedFont() {
    static sf::Font font;
    static bool loaded = false;
    if (!loaded) { font.loadFromFile("data/DungGeunMo.ttf"); loaded = true; }
    return font;
}

Tower::Tower(const TowerDescription& desc)
    : GameObject(Tag::Tower),
      description(desc),
      gridPosition(0, 0) {
    shape.setSize({46.f, 46.f});
    shape.setFillColor(description.color);
}

void Tower::upgrade() {
    if (!isMaxLevel()) ++level;
}

void Tower::kill() {
    alive = false;
}

void Tower::setGridPosition(sf::Vector2i pos) {
    gridPosition = pos;
}

void Tower::update() {}

bool Tower::isAlive() const {
    return alive;
}

void Tower::render(sf::RenderWindow& win) {
    shape.setFillColor(description.color);
    shape.setPosition(position + sf::Vector2f(2,2));
    win.draw(shape);

    if (level > 0) {
        sf::Text lvText(std::to_string(level), getSharedFont(), 14);
        lvText.setFillColor(sf::Color::White);
        lvText.setPosition(position.x + 32.f, position.y + 2.f);
        win.draw(lvText);
    }
}

RenderLayer Tower::getLayer() const {
    return RenderLayer::Entity;
}
