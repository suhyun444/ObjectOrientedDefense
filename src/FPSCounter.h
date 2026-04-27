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
    sf::Font m_font;
    sf::Text m_text;
    int      m_frameCount = 0;
    float    m_elapsed    = 0.f;
    int      m_fps        = 0;
};
