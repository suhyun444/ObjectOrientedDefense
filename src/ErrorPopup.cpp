#include "ErrorPopup.h"
#include <cstring>
#include <iostream>

ErrorPopup::ErrorPopup(sf::RenderWindow& window, std::function<void()> onOk)
    : onOk(std::move(onOk))
{
    if (!font.loadFromFile("data/DungGeunMo.ttf"))
        std::cerr << "[ErrorPopup] 폰트 로딩 실패\n";

    const float winW   = static_cast<float>(window.getSize().x);
    const float winH   = static_cast<float>(window.getSize().y);
    const float panelW = 500.f, panelH = 280.f;
    const float panelX = (winW - panelW) / 2.f;
    const float panelY = (winH - panelH) / 2.f;
    const float btnW   = 160.f, btnH = 50.f;
    const float btnX   = panelX + (panelW - btnW) / 2.f;
    const float btnY   = panelY + panelH - btnH - 25.f;

    okBounds = { btnX, btnY, btnW, btnH };

    overlay.setSize({ winW, winH });
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    panel.setSize({ panelW, panelH });
    panel.setPosition(panelX, panelY);
    panel.setFillColor(sf::Color(30, 30, 30));

    const char* titleStr = u8"Wave 정보 오류";
    titleText.setFont(font);
    titleText.setCharacterSize(32);
    titleText.setString(sf::String::fromUtf8(titleStr, titleStr + std::strlen(titleStr)));
    titleText.setFillColor(sf::Color(220, 50, 50));
    {
        sf::FloatRect b = titleText.getLocalBounds();
        titleText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        titleText.setPosition(panelX + panelW / 2.f, panelY + 55.f);
    }

    messageText.setFont(font);
    messageText.setCharacterSize(16);
    messageText.setString("Wave data is corrupted.\nPlease reinstall the game.");
    messageText.setFillColor(sf::Color(200, 200, 200));
    {
        sf::FloatRect b = messageText.getLocalBounds();
        messageText.setOrigin(b.left + b.width / 2.f, b.top);
        messageText.setPosition(panelX + panelW / 2.f, panelY + 110.f);
    }

    okButton.setSize({ btnW, btnH });
    okButton.setPosition(btnX, btnY);
    okButton.setFillColor(sf::Color(180, 50, 50));

    const char* okStr = u8"종료";
    okText.setFont(font);
    okText.setCharacterSize(22);
    okText.setString(sf::String::fromUtf8(okStr, okStr + std::strlen(okStr)));
    okText.setFillColor(sf::Color::White);
    {
        sf::FloatRect b = okText.getLocalBounds();
        okText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        okText.setPosition(btnX + btnW / 2.f, btnY + btnH / 2.f);
    }
}

void ErrorPopup::render(sf::RenderWindow& window) {
    window.draw(overlay);
    window.draw(panel);
    window.draw(titleText);
    window.draw(messageText);
    window.draw(okButton);
    window.draw(okText);
}

bool ErrorPopup::containsPoint(const sf::Vector2i& pos) const {
    lastMousePos = pos;
    return true;
}

bool ErrorPopup::onClick() {
    if (okBounds.contains(static_cast<float>(lastMousePos.x), static_cast<float>(lastMousePos.y))) {
        if (onOk) onOk();
    }
    return true;
}
