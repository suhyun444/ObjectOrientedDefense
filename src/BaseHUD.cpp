#include "BaseHUD.h"

#include <iostream>

#include "Base.h"

BaseHUD::BaseHUD(const Base* base) : base(base) {
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

void BaseHUD::render(sf::RenderWindow& window) {
    hpText.setString("HP: " + std::to_string(base->getHp()));
    goldText.setString("Gold: " + std::to_string(base->getGold()));
    window.draw(hpText);
    window.draw(goldText);
}

RenderLayer BaseHUD::getLayer() const {
    return RenderLayer::UI;
}
