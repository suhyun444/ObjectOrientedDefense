#include "GameResultPopup.h"
#include <cstring>

static constexpr float WIN_W  = 1530.f;
static constexpr float WIN_H  = 750.f;
static constexpr float PANEL_W = 400.f;
static constexpr float PANEL_H = 260.f;
static constexpr float PANEL_X = (WIN_W - PANEL_W) / 2.f;
static constexpr float PANEL_Y = (WIN_H - PANEL_H) / 2.f;
static constexpr float BTN_W  = 160.f;
static constexpr float BTN_H  = 50.f;
static constexpr float BTN_X  = PANEL_X + (PANEL_W - BTN_W) / 2.f;
static constexpr float BTN_Y  = PANEL_Y + PANEL_H - BTN_H - 25.f;

GameResultPopup::GameResultPopup(bool isVictory, std::function<void()> onYes)
    : onYes(std::move(onYes))
    , yesBounds(BTN_X, BTN_Y, BTN_W, BTN_H)
{
    font.loadFromFile("data/DungGeunMo.ttf");

    overlay.setSize({ WIN_W, WIN_H });
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    panel.setSize({ PANEL_W, PANEL_H });
    panel.setPosition(PANEL_X, PANEL_Y);
    panel.setFillColor(sf::Color(30, 30, 30));

    titleText.setFont(font);
    titleText.setCharacterSize(36);
    titleText.setString(isVictory ? "GAME CLEAR!" : "GAME OVER!");
    titleText.setFillColor(isVictory ? sf::Color(255, 215, 0) : sf::Color(220, 50, 50));
    {
        sf::FloatRect b = titleText.getLocalBounds();
        titleText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        titleText.setPosition(PANEL_X + PANEL_W / 2.f, PANEL_Y + 70.f);
    }

    const char* subStr = u8"게임을 종료할까요?";
    subtitleText.setFont(font);
    subtitleText.setCharacterSize(20);
    subtitleText.setString(sf::String::fromUtf8(subStr, subStr + std::strlen(subStr)));
    subtitleText.setFillColor(sf::Color(180, 180, 180));
    {
        sf::FloatRect b = subtitleText.getLocalBounds();
        subtitleText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        subtitleText.setPosition(PANEL_X + PANEL_W / 2.f, PANEL_Y + 140.f);
    }

    yesButton.setSize({ BTN_W, BTN_H });
    yesButton.setPosition(BTN_X, BTN_Y);
    yesButton.setFillColor(sf::Color(60, 120, 200));

    yesText.setFont(font);
    yesText.setCharacterSize(22);
    yesText.setString("YES");
    yesText.setFillColor(sf::Color::White);
    {
        sf::FloatRect b = yesText.getLocalBounds();
        yesText.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        yesText.setPosition(BTN_X + BTN_W / 2.f, BTN_Y + BTN_H / 2.f);
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
