#include "PlayerHUD.h"

#include <iostream>

#include "Player.h"

PlayerHUD::PlayerHUD(const Player* player) : player(player) {
    if (!font.loadFromFile("data/DungGeunMo.ttf")) return;

    hpText.setFont(font);
    hpText.setCharacterSize(18);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(10.f, 10.f);

    goldText.setFont(font);
    goldText.setCharacterSize(18);
    goldText.setFillColor(sf::Color::White);
    goldText.setPosition(10.f, 35.f);
}

void PlayerHUD::render(sf::RenderWindow& window) {
    hpText.setString("HP: " + std::to_string(player->getHp()));
    goldText.setString("Gold: " + std::to_string(player->getGold()));
    window.draw(hpText);
    window.draw(goldText);
}

RenderLayer PlayerHUD::getLayer() const {
    return RenderLayer::UI;
}
