#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "IRenderable.h"

class Renderer {
private:
    sf::RenderWindow window;
    std::vector<std::weak_ptr<IRenderable>> renderables;

public:
    Renderer(unsigned int width, unsigned int height, const std::string& title);
    
    sf::RenderWindow& getWindow();
    bool isWindowOpen() const;

    void addRenderable(std::weak_ptr<IRenderable> renderable);
    void drawAll();
};