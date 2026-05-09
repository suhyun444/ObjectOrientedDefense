#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "IRenderable.h"
#include "IClickable.h"

class ErrorPopup : public IRenderable, public IClickable {
    sf::Font font;
    sf::RectangleShape overlay;
    sf::RectangleShape panel;
    sf::RectangleShape okButton;
    sf::Text titleText;
    sf::Text messageText;
    sf::Text okText;
    sf::FloatRect okBounds;
    std::function<void()> onOk;
    mutable sf::Vector2i lastMousePos;

public:
    ErrorPopup(sf::RenderWindow& window, std::function<void()> onOk);

    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override { return RenderLayer::UI; }
    bool containsPoint(const sf::Vector2i& pos) const override;
    bool onClick() override;
};
