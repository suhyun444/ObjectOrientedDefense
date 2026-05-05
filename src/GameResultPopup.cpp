#include "GameResultPopup.h"
#include <cstring>
#include <iostream>

GameResultPopup::GameResultPopup(bool isVictory, sf::RenderWindow& window, std::function<void()> onYes)
    : onYes(std::move(onYes))
{
    if (!font.loadFromFile("data/DungGeunMo.ttf"))
        std::cerr << "[GameResultPopup] 폰트 로딩 실패\n";

    const float winW   = static_cast<float>(window.getSize().x);
    const float winH   = static_cast<float>(window.getSize().y);
    const float panelW = 400.f, panelH = 260.f;
    const float panelX = (winW - panelW) / 2.f;
    const float panelY = (winH - panelH) / 2.f;
    const float btnW   = 160.f, btnH = 50.f;
    const float btnX   = panelX + (panelW - btnW) / 2.f;
    const float btnY   = panelY + panelH - btnH - 25.f;

    yesBounds = { btnX, btnY, btnW, btnH };

    overlay.setSize({ winW, winH });
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    panel.setSize({ panelW, panelH });
    panel.setPosition(panelX, panelY);
    panel.setFillColor(sf::Color(30, 30, 30));

    titleText.setFont(font);
    titleText.setCharacterSize(36);
    titleText.setString(isVictory ? "GAME CLEAR!" : "GAME OVER!");
    titleText.setFillColor(isVictory ? sf::Color(255, 215, 0) : sf::Color(220, 50, 50));
    {
        sf::FloatRect b = titleText.getLocalBounds();
        titleText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        titleText.setPosition(panelX + panelW / 2.f, panelY + 70.f);
    }

    const char* subStr = u8"게임을 종료할까요?";
    subtitleText.setFont(font);
    subtitleText.setCharacterSize(20);
    subtitleText.setString(sf::String::fromUtf8(subStr, subStr + std::strlen(subStr)));
    subtitleText.setFillColor(sf::Color(180, 180, 180));
    {
        sf::FloatRect b = subtitleText.getLocalBounds();
        subtitleText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        subtitleText.setPosition(panelX + panelW / 2.f, panelY + 140.f);
    }

    yesButton.setSize({ btnW, btnH });
    yesButton.setPosition(btnX, btnY);
    yesButton.setFillColor(sf::Color(60, 120, 200));

    yesText.setFont(font);
    yesText.setCharacterSize(22);
    yesText.setString("YES");
    yesText.setFillColor(sf::Color::White);
    {
        sf::FloatRect b = yesText.getLocalBounds();
        yesText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        yesText.setPosition(btnX + btnW / 2.f, btnY + btnH / 2.f);
    }
}

void GameResultPopup::render(sf::RenderWindow& window) {
    window.draw(overlay);
    window.draw(panel);
    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(yesButton);
    window.draw(yesText);
}

bool GameResultPopup::containsPoint(const sf::Vector2i& pos) const {
    lastMousePos = pos;
    return true;
}

bool GameResultPopup::onClick() {
    if (yesBounds.contains(static_cast<float>(lastMousePos.x), static_cast<float>(lastMousePos.y))) {
        if (onYes) onYes();
    }
    return true;
}
