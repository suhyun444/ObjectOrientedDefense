#pragma once
#include <SFML/Graphics/Color.hpp>
#include <string>

enum class TowerType {
    Basic,
    Ice,
    Sniper,
    Explosion
};

struct TowerDescription {
    TowerType   type          = TowerType::Basic;
    int         cost          = 50;
    int         damage        = 10;
    float       range         = 170.f;
    float       fireRate      = 1.25f;
    int         damagePerLevel = 5;
    int         upgradeCost   = 30;
    int         maxLevel      = 3;
    sf::Color   color         = sf::Color::Blue;
    std::string name          = "Basic";
};
