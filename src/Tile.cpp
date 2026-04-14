#include "Tile.h"
#include "Timer.h"
#include <iostream>

Tile::Tile(int gridX, int gridY, TileType type)
    : GameObject(Tag::Tile), gridX(gridX), gridY(gridY), type(type), timeAccumulator(0.f) {
    
    // 1. 그리드 인덱스를 픽셀 좌표로 변환 (타일 크기 50x50)
    float tileSize = 50.f;
    position = {gridX * tileSize, gridY * tileSize};

    // 2. 사각형 렌더링 세팅 (그리드 선이 보이도록 2픽셀 작게 설정)
    shape.setSize({tileSize - 2.f, tileSize - 2.f});
    shape.setPosition(position);

    // 3. 타입별 색상 지정
    switch (type) {
        case TileType::Buildable: shape.setFillColor(sf::Color(46, 204, 113)); break; // 초록
        case TileType::Path:      shape.setFillColor(sf::Color(149, 165, 166)); break; // 회색
        case TileType::Occupied:  shape.setFillColor(sf::Color(231, 76, 60)); break;  // 빨강
    }
}

void Tile::setType(TileType newType) {
    type = newType;
    switch (type) {
        case TileType::Buildable: shape.setFillColor(sf::Color(46, 204, 113)); break;
        case TileType::Path:      shape.setFillColor(sf::Color(149, 165, 166)); break;
        case TileType::Occupied:  shape.setFillColor(sf::Color(231, 76, 60)); break;
    }
}

void Tile::update() {

}

void Tile::render(sf::RenderWindow& window) {
    // Renderer가 이 함수를 호출하여 화면에 그림
    window.draw(shape);
}

RenderLayer Tile::getLayer() const {
    return RenderLayer::Background; // 가장 밑바탕
}