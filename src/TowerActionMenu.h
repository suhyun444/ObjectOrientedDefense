#pragma once
#include "IRoutine.h"
#include "IRenderable.h"
#include "IClickable.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Tower;
class Tile;
class InputManager;

class TowerActionMenu : public IRoutine, public IRenderable, public IClickable {
public:
    std::function<void()> onUpgrade;
    std::function<void()> onRemove;

    TowerActionMenu(Tower* tower, Tile* tile, InputManager* im);

    bool isAlive() const override { return alive; }
    void kill()                   { alive = false; }

    void update() override;
    void render(sf::RenderWindow& win) override;
    RenderLayer getLayer() const override { return RenderLayer::UI; }

    bool containsPoint(const sf::Vector2i& pos) const override;
    bool onClick() override;
    bool isEnabled() const override { return true; }

private:
    Tower*        tower;
    Tile*         tile;
    InputManager* inputManager;
    bool          alive        = true;
    bool          prevMouseDown = false;

    float menuX, menuY;

    static constexpr float BTN_W = 160.f;
    static constexpr float BTN_H = 36.f;
    static constexpr float GAP   = 6.f;

    sf::Font& font();
    sf::FloatRect upgradeRect() const;
    sf::FloatRect removeRect()  const;
};
