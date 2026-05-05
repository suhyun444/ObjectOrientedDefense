#pragma once

#include <SFML/Graphics.hpp>
#include "IRoutine.h"
#include "IRenderable.h"

class GoldNotice : public IRoutine, public IRenderable {
    sf::Font font;
    sf::Text text;
    sf::RectangleShape bg;
    float elapsed = 0.f;
    bool alive = true;
    static constexpr float DURATION = 2.f;

public:
    GoldNotice();
    void kill() { alive = false; }

    void update() override;
    bool isAlive() const override { return alive; }
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override { return RenderLayer::UI; }
};
