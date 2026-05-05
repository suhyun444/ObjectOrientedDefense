#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "IRenderable.h"
#include "IClickable.h"

class GameResultPopup : public IRenderable, public IClickable {
    sf::Font font;
    sf::RectangleShape overlay;
    sf::RectangleShape panel;
    sf::RectangleShape yesButton;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text yesText;
    sf::FloatRect yesBounds;
    std::function<void()> onYes;
    mutable sf::Vector2i lastMousePos;

public:
    GameResultPopup(bool isVictory, std::function<void()> onYes);

    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override { return RenderLayer::UI; }
    bool containsPoint(const sf::Vector2i& pos) const override;
    bool onClick() override;
};
