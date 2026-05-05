#include "GoldNotice.h"
#include "Time.h"

GoldNotice::GoldNotice() {
    if (!font.loadFromFile("data/DungGeunMo.ttf")) return;

    text.setFont(font);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color::Yellow);
    text.setString("Not enough gold!");

    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    text.setPosition(650.f, 375.f);

    bg.setSize({ bounds.width + 40.f, bounds.height + 24.f });
    bg.setFillColor(sf::Color(0, 0, 0, 160));
    bg.setOrigin(bg.getSize().x / 2.f, bg.getSize().y / 2.f);
    bg.setPosition(650.f, 375.f);
}

void GoldNotice::update() {
    elapsed += Time::getDeltaTime();
    if (elapsed >= DURATION) alive = false;
}

void GoldNotice::render(sf::RenderWindow& window) {
    window.draw(bg);
    window.draw(text);
}
