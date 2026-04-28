#include "WaveStartButton.h"
#include "Wave.h"
#include "ObjectFactory.h"
#include "GameManager.h"
#include <fstream>
#include <iostream>

static const float BTN_X      = 1050.f;
static const float BTN_Y      = 640.f;
static const float BTN_WIDTH  = 200.f;
static const float BTN_HEIGHT = 50.f;

WaveStartButton::WaveStartButton(Wave* wave)
    : nextLevel(1),
      wave(wave){
    shape.setSize({BTN_WIDTH, BTN_HEIGHT});
    shape.setPosition(BTN_X, BTN_Y);

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    label.setFont(font);
    label.setCharacterSize(16);
    label.setFillColor(sf::Color::White);

    updateVisual();
}


bool WaveStartButton::isEnabled() const {
    std::cout << "check button isEnabled\n";
    std::cout << "Wave status : " << wave->isComplete() << "\n";
    return wave->isComplete();
}

bool WaveStartButton::containsPoint(const sf::Vector2i& pixelPos) const {
    return pixelPos.x >= BTN_X && pixelPos.x < BTN_X + BTN_WIDTH
        && pixelPos.y >= BTN_Y && pixelPos.y < BTN_Y + BTN_HEIGHT;
}

bool WaveStartButton::onClick() {
    wave->loadFromFile();
    ++nextLevel;
    updateVisual();
    return true;
}

void WaveStartButton::update() {
    updateVisual();
}

void WaveStartButton::updateVisual() {
    if (!wave->isComplete()) {
        shape.setFillColor(sf::Color(100, 100, 100));
        label.setString("  진행 중...");
    }
    else
    {
        shape.setFillColor(sf::Color(34, 139, 34));
        label.setString(" Wave " + std::to_string(nextLevel) + " 시작");
    }
    label.setPosition(BTN_X + 10.f, BTN_Y + 14.f);
}

void WaveStartButton::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(label);
}

RenderLayer WaveStartButton::getLayer() const {
    return RenderLayer::UI;
}

bool WaveStartButton::isAlive() const {
    return true;
}
