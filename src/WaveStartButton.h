#pragma once

#include "IRoutine.h"
#include "IRenderable.h"
#include "IClickable.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class Wave;
class Path;
class GameManager;

class WaveStartButton : public IRoutine, public IRenderable, public IClickable {
private:
    int nextLevel;
    Wave* wave;
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text label;

public:
    WaveStartButton(Wave* wave);

    // IClickable
    bool containsPoint(const sf::Vector2i& pixelPos) const override;
    bool onClick() override;
    bool isEnabled() const override;

    // IRenderable
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;

    // IRoutine
    void update() override;
    bool isAlive() const override;

private:
    void updateVisual();
};
