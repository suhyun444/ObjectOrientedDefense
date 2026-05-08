#pragma once
#include "IRenderable.h"
#include <SFML/Graphics.hpp>

class Base;

class BaseHUD : public IRenderable {
public:
    explicit BaseHUD(const Base* base);
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
private:
    const Base* base;
    sf::Font font;
    sf::Text hpText;
    sf::Text goldText;
};
