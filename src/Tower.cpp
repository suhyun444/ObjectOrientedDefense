#include "Tower.h"
#include "Monster.h"
#include "Time.h"
#include <cmath>

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
    if (isMaxLevel()) return;
    ++level;
    description.damage += description.damagePerLevel;
}

void Tower::kill() {
    alive = false;
}

void Tower::setGridPosition(sf::Vector2i pos) {
    gridPosition = pos;
}

void Tower::setMonstersProvider(std::function<std::vector<std::shared_ptr<Monster>>()> fn) {
    monstersProvider = std::move(fn);
}

void Tower::update() {
    fireCooldown -= Time::getDeltaTime();
    if (fireCooldown > 0.f || !monstersProvider) return;
    auto target = getTarget(monstersProvider());
    if (!target) return;
    fire(target);
    fireCooldown = 1.0f / description.fireRate;
}

std::shared_ptr<Monster> Tower::findMostAdvancedTarget(
    const std::vector<std::shared_ptr<Monster>>& monsters) const
{
    std::shared_ptr<Monster> best;
    int bestWP = -1;
    for (const auto& m : monsters) {
        sf::Vector2f diff = m->getPosition() - position;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        if (dist > description.range) continue;
        int wp = m->getWaypointIndex();
        if (wp > bestWP) {
            bestWP = wp;
            best = m;
        }
    }
    return best;
}

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
