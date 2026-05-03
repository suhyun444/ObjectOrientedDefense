#include "TowerActionMenu.h"
#include "Tower.h"
#include "Tile.h"
#include "InputManager.h"
#include <SFML/Window/Mouse.hpp>

TowerActionMenu::TowerActionMenu(Tower* tw, Tile* tl, InputManager* im)
    : tower(tw), tile(tl), inputManager(im) {
    auto pos = tl->getPosition();
    menuX = pos.x - (BTN_W - 50.f) / 2.f;
    menuY = pos.y - BTN_H * 2.f - GAP * 3.f;
    if (menuY < 0.f) menuY = pos.y + 55.f;
}

sf::Font& TowerActionMenu::font() {
    static sf::Font f;
    static bool loaded = false;
    if (!loaded) { f.loadFromFile("data/DungGeunMo.ttf"); loaded = true; }
    return f;
}

sf::FloatRect TowerActionMenu::upgradeRect() const {
    return { menuX, menuY, BTN_W, BTN_H };
}

sf::FloatRect TowerActionMenu::removeRect() const {
    return { menuX, menuY + BTN_H + GAP, BTN_W, BTN_H };
}

bool TowerActionMenu::containsPoint(const sf::Vector2i& pos) const {
    auto ur = upgradeRect();
    auto rr = removeRect();
    auto inRect = [&](const sf::FloatRect& r) {
        return pos.x >= r.left && pos.x < r.left + r.width &&
               pos.y >= r.top  && pos.y < r.top  + r.height;
    };
    return inRect(ur) || inRect(rr);
}

void TowerActionMenu::update() {
    if (!alive) return;
    bool currentDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if (prevMouseDown && !currentDown) {
        auto pos = inputManager->getMousePosition();
        if (!containsPoint(pos)) alive = false;
    }
    prevMouseDown = currentDown;
}

void TowerActionMenu::render(sf::RenderWindow& win) {
    if (!alive) return;

    const auto& desc = tower->getDescription();

    auto drawBtn = [&](const sf::FloatRect& r, sf::Color col, const std::string& label) {
        sf::RectangleShape btn({ r.width, r.height });
        btn.setPosition(r.left, r.top);
        btn.setFillColor(col);
        win.draw(btn);
        sf::Text t(label, font(), 14);
        t.setFillColor(sf::Color::White);
        t.setPosition(r.left + 8.f, r.top + 9.f);
        win.draw(t);
    };

    bool maxed = tower->isMaxLevel();
    std::string upLabel = maxed
        ? "Upgrade (MAX)"
        : "Upgrade (+" + std::to_string(desc.damagePerLevel) + "dmg " + std::to_string(desc.upgradeCost) + "G)";
    std::string rmLabel = "Remove (refund " + std::to_string(tower->getRefundGold()) + "G)";

    drawBtn(upgradeRect(), maxed ? sf::Color(100,100,100) : sf::Color(60,120,200), upLabel);
    drawBtn(removeRect(),  sf::Color(180, 60, 60), rmLabel);
}

bool TowerActionMenu::onClick() {
    auto pos = inputManager->getMousePosition();

    auto inRect = [&](const sf::FloatRect& r) {
        return pos.x >= r.left && pos.x < r.left + r.width &&
               pos.y >= r.top  && pos.y < r.top  + r.height;
    };

    if (inRect(upgradeRect())) {
        if (!tower->isMaxLevel() && onUpgrade) onUpgrade();
        alive = false;
        return true;
    }
    if (inRect(removeRect())) {
        if (onRemove) onRemove();
        alive = false;
        return true;
    }
    return false;
}
