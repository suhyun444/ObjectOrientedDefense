#pragma once
#include "IRenderable.h"
#include <SFML/Graphics.hpp>

class Player;

class PlayerHUD : public IRenderable {
public:
    explicit PlayerHUD(const Player* player);
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
private:
    const Player* player;
    sf::Font font;
    sf::Text hpText;
    sf::Text goldText;
};
