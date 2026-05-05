#include "TowerSelectPanel.h"
#include "InputManager.h"
#include "BasicTower.h"
#include "IceTower.h"
#include "SniperTower.h"
#include "ExplosionTower.h"
#include "Tile.h"

TowerSelectPanel::TowerSelectPanel(Tile* tile, InputManager* im)
    : selectedTile(tile), inputManager(im) {
    descriptions = {
        BasicTower{}.getDescription(),
        IceTower{}.getDescription(),
        SniperTower{}.getDescription(),
        ExplosionTower{}.getDescription(),
    };
    types = { TowerType::Basic, TowerType::Ice, TowerType::Sniper, TowerType::Explosion };
}

sf::Font& TowerSelectPanel::font() {
    static sf::Font f;
    static bool loaded = false;
    if (!loaded) { f.loadFromFile("data/DungGeunMo.ttf"); loaded = true; }
    return f;
}

sf::FloatRect TowerSelectPanel::cardRect(int i) const {
    return { PANEL_X + 5.f, PANEL_Y + HEADER_H + i * CARD_H, PANEL_W - 10.f, CARD_H - 5.f };
}

sf::FloatRect TowerSelectPanel::closeBtnRect() const {
    return { PANEL_X + PANEL_W - 35.f, PANEL_Y + 8.f, 27.f, 27.f };
}

void TowerSelectPanel::update() {
    if (!alive) return;
    auto mousePos = inputManager->getMousePosition();
    hoveredCard = -1;
    for (int i = 0; i < (int)descriptions.size(); i++) {
        auto r = cardRect(i);
        if (mousePos.x >= r.left && mousePos.x < r.left + r.width &&
            mousePos.y >= r.top  && mousePos.y < r.top  + r.height) {
            hoveredCard = i;
            break;
        }
    }
}

void TowerSelectPanel::render(sf::RenderWindow& win) {
    if (!alive) return;

    // 패널 배경
    sf::RectangleShape bg({ PANEL_W, 750.f });
    bg.setPosition(PANEL_X, PANEL_Y);
    bg.setFillColor(sf::Color(40, 40, 40, 220));
    win.draw(bg);

    // X 버튼
    auto cr = closeBtnRect();
    sf::RectangleShape xBtn({ cr.width, cr.height });
    xBtn.setPosition(cr.left, cr.top);
    xBtn.setFillColor(sf::Color(180, 50, 50));
    win.draw(xBtn);
    sf::Text xText(std::string("X"), font(), 16);
    xText.setFillColor(sf::Color::White);
    xText.setPosition(cr.left + 7.f, cr.top + 3.f);
    win.draw(xText);

    // 타워 카드
    for (int i = 0; i < (int)descriptions.size(); i++) {
        const auto& desc = descriptions[i];
        auto r = cardRect(i);
        bool hovered = (hoveredCard == i);

        sf::RectangleShape card({ r.width, r.height });
        card.setPosition(r.left, r.top);
        card.setFillColor(hovered ? sf::Color(70, 70, 90, 220) : sf::Color(55, 55, 75, 200));
        card.setOutlineThickness(1.f);
        card.setOutlineColor(sf::Color(120, 120, 140));
        win.draw(card);

        // 타워 모양 미리보기
        sf::RectangleShape preview({ 38.f, 38.f });
        preview.setPosition(r.left + 8.f, r.top + 12.f);
        preview.setFillColor(desc.color);
        win.draw(preview);

        // 텍스트
        float tx = r.left + 56.f;
        auto makeText = [&](const std::string& str, float y, unsigned size = 14) {
            sf::Text t(str, font(), size);
            t.setFillColor(sf::Color::White);
            t.setPosition(tx, r.top + y);
            win.draw(t);
        };

        makeText(desc.name, 8.f, 16);
        makeText("DMG: " + std::to_string(desc.damage), 32.f);
        makeText("Cost: " + std::to_string(desc.cost) + "G", 52.f);

    }

    // hover 중인 카드가 있으면 선택된 타일 중심에 사거리 원 표시
    if (hoveredCard >= 0) {
        float r = descriptions[hoveredCard].range;
        auto tilePos = selectedTile->getPosition();
        float cx = tilePos.x + 25.f;
        float cy = tilePos.y + 25.f;

        sf::CircleShape circle(r);
        circle.setPosition(cx - r, cy - r);
        circle.setFillColor(sf::Color(255, 255, 255, 30));
        circle.setOutlineThickness(1.5f);
        circle.setOutlineColor(descriptions[hoveredCard].color);
        win.draw(circle);
    }
}

bool TowerSelectPanel::containsPoint(const sf::Vector2i& pos) const {
    return pos.x >= PANEL_X && pos.x < PANEL_X + PANEL_W &&
           pos.y >= PANEL_Y && pos.y < PANEL_Y + 750.f;
}

bool TowerSelectPanel::onClick() {
    // X 버튼 클릭
    auto pos = inputManager->getMousePosition();
    auto cr = closeBtnRect();
    if (pos.x >= cr.left && pos.x < cr.left + cr.width &&
        pos.y >= cr.top  && pos.y < cr.top  + cr.height) {
        if (onClose) onClose();
        alive = false;
        return true;
    }

    // 카드 클릭
    for (int i = 0; i < (int)descriptions.size(); i++) {
        auto r = cardRect(i);
        if (pos.x >= r.left && pos.x < r.left + r.width &&
            pos.y >= r.top  && pos.y < r.top  + r.height) {
            if (onSelectTower) {
                if (onSelectTower(types[i], descriptions[i].cost))
                    alive = false;
            }
            return true;
        }
    }

    return true;
}
