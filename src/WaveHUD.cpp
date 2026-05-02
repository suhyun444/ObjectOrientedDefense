#include "WaveHUD.h"
#include "Wave.h"

WaveHUD::WaveHUD(const Wave* wave) : wave(wave) {
    if (!font.loadFromFile("data/DungGeunMo.ttf")) return;

    waveText.setFont(font);
    waveText.setCharacterSize(18);
    waveText.setFillColor(sf::Color::White);
    waveText.setPosition(10.f, 60.f);
}

void WaveHUD::render(sf::RenderWindow& window) {
    waveText.setString("Wave: " + std::to_string(wave->GetLevel() + 1));
    window.draw(waveText);
}

RenderLayer WaveHUD::getLayer() const {
    return RenderLayer::UI;
}
