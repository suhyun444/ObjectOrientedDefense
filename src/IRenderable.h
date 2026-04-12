#pragma once
#include <SFML/Graphics.hpp>

// 그리기 우선순위 (숫자가 높을수록 나중에(위에) 그려짐)
enum class RenderLayer {
    Background = 0, // Tile, Map
    Entity = 1,     // Monster, Tower
    Projectile = 2, // 투사체
    UI = 3          // 버튼, 팝업
};

class IRenderable {
public:
    virtual ~IRenderable() = default;
    
    // SFML 윈도우에 자신을 그리는 순수 가상 함수
    virtual void render(sf::RenderWindow& window) = 0;
    
    // 자신의 레이어를 반환하는 순수 가상 함수
    virtual RenderLayer getLayer() const = 0;
};