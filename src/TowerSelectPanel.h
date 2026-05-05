#pragma once
#include "IRoutine.h"
#include "IRenderable.h"
#include "IClickable.h"
#include "TowerDescription.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

class Tile;
class InputManager;

class TowerSelectPanel : public IRoutine, public IRenderable, public IClickable {
public:
    std::function<bool(TowerType, int)> onSelectTower;
    std::function<void()>               onClose;

    TowerSelectPanel(Tile* tile, InputManager* im);

    bool isAlive() const override { return alive; }
    void kill()                   { alive = false; }

    void update() override;
    void render(sf::RenderWindow& win) override;
    RenderLayer getLayer() const override { return RenderLayer::UI; }

    bool containsPoint(const sf::Vector2i& pos) const override;
    bool onClick() override;
    bool isEnabled() const override { return true; }

private:
    static constexpr float PANEL_X   = 1300.f;
    static constexpr float PANEL_Y   = 0.f;
    static constexpr float PANEL_W   = 230.f;
    static constexpr float CARD_H    = 165.f;
    static constexpr float HEADER_H  = 45.f;

    Tile*         selectedTile;
    InputManager* inputManager;
    bool          alive       = true;
    int           hoveredCard = -1;

    std::vector<TowerDescription> descriptions;
    std::vector<TowerType>        types;

    sf::Font& font();
    sf::FloatRect cardRect(int i) const;
    sf::FloatRect closeBtnRect() const;
};
