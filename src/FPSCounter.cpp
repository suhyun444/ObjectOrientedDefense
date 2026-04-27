#include "FPSCounter.h"
#include "Time.h"

FPSCounter::FPSCounter() : GameObject(Tag::Default) {
    if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) return;
    m_text.setFont(m_font);
    m_text.setCharacterSize(18);
    m_text.setFillColor(sf::Color::White);
    m_text.setPosition(1140.f, 8.f);
    m_text.setString("FPS: --");
}

void FPSCounter::update() {
    m_frameCount++;
    m_elapsed += Time::getDeltaTime();
    if (m_elapsed >= 1.0f) {
        m_fps = static_cast<int>(m_frameCount / m_elapsed);
        m_text.setString("FPS: " + std::to_string(m_fps));
        m_frameCount = 0;
        m_elapsed = 0.f;
    }
}

void FPSCounter::render(sf::RenderWindow& window) {
    window.draw(m_text);
}

RenderLayer FPSCounter::getLayer() const {
    return RenderLayer::UI;
}
