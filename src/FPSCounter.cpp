#include "FPSCounter.h"
#include "Time.h"

FPSCounter::FPSCounter() : GameObject(Tag::Default) {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) return;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setPosition(1140.f, 8.f);
    text.setString("FPS: --");
}

void FPSCounter::update() {
    frameCount++;
    elapsed += Time::getDeltaTime();
    if (elapsed >= 1.0f) {
        fps = static_cast<int>(frameCount / elapsed);
        text.setString("FPS: " + std::to_string(fps));
        frameCount = 0;
        elapsed = 0.f;
    }
}

void FPSCounter::render(sf::RenderWindow& window) {
    window.draw(text);
}

RenderLayer FPSCounter::getLayer() const {
    return RenderLayer::UI;
}
