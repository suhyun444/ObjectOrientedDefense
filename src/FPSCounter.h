#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class FPSCounter : public GameObject {
public:
    FPSCounter();

    void update() override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;

private:
    sf::Font font;
    sf::Text text;
    int      frameCount = 0;
    float    elapsed    = 0.f;
    int      fps        = 0;
};
