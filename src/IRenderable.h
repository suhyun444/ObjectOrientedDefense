#pragma once
#include <SFML/Graphics.hpp>

enum class RenderLayer {
    Background = 0, 
    Entity = 1, 
    Projectile = 2, 
    UI = 3   
};

class IRenderable {
public:
    virtual ~IRenderable() = default;
    
    virtual void render(sf::RenderWindow& window) = 0;
    
    virtual RenderLayer getLayer() const = 0;
};