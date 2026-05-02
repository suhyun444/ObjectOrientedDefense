#pragma once
#include "IRenderable.h"
#include <SFML/Graphics.hpp>

class Wave;

class WaveHUD : public IRenderable {
public:
    explicit WaveHUD(const Wave* wave);
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
private:
    const Wave* wave;
    sf::Font font;
    sf::Text waveText;
};
