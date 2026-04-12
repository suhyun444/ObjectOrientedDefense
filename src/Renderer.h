#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "IRenderable.h"

class Renderer {
private:
    sf::RenderWindow window; // 내부에서 윈도우 소유
    std::vector<std::weak_ptr<IRenderable>> renderables;

public:
    // 생성자에서 윈도우 초기화
    Renderer(unsigned int width, unsigned int height, const std::string& title);
    
    // 윈도우 객체 반환 (InputManager 등이 이벤트 처리를 위해 필요함)
    sf::RenderWindow& getWindow();
    bool isWindowOpen() const;

    void addRenderable(std::weak_ptr<IRenderable> renderable);
    void drawAll();
};