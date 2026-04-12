#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RectangleShape.hpp>

enum class TileType {
    Buildable, // 초록색
    Path,      // 회색
    Occupied   // 빨간색
};

class Tile : public GameObject {
private:
    TileType type;
    sf::RectangleShape shape;
    int gridX;
    int gridY;
    
    // 콘솔 스팸(프레임 드랍) 방지용 누적 시간 타이머
    float timeAccumulator; 

public:
    Tile(int gridX, int gridY, TileType type);

    TileType getType() const { return type; }
    void setType(TileType newType);

    void update() override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};