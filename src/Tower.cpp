#include "Tower.h"
#include "Monster.h"
#include "Time.h"
#include "MostAdvancedTargeting.h"

static sf::Font& getSharedFont() {
    static sf::Font font;
    static bool loaded = false;
    if (!loaded) { font.loadFromFile("data/DungGeunMo.ttf"); loaded = true; }
    return font;
}

Tower::Tower(const TowerDescription& desc)
    : GameObject(Tag::Tower),
      description(desc),
      gridPosition(0, 0),
      targetingStrategy(std::make_unique<MostAdvancedTargeting>()) {
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

void Tower::setTargetingStrategy(std::unique_ptr<ITargetingStrategy> s) {
    targetingStrategy = std::move(s);
}

void Tower::update() {
    fireCooldown -= Time::getDeltaTime();
    if (fireCooldown > 0.f || !monstersProvider) return;
    auto target = selectTarget(monstersProvider());
    if (!target) return;
    createProjectile(target);
    fireCooldown = 1.0f / description.fireRate;
}

std::shared_ptr<Monster> Tower::selectTarget(
    const std::vector<std::shared_ptr<Monster>>& monsters) const
{
    return targetingStrategy->selectTarget(position, description.range, monsters);
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
