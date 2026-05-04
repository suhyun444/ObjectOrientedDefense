#pragma once
#include "GameObject.h"

class ExplosionEffect : public GameObject {
    float elapsed = 0.f;
    static constexpr float DURATION   = 0.4f;
    static constexpr float MAX_RADIUS = 80.f;
public:
    explicit ExplosionEffect(sf::Vector2f pos);
    void update() override;
    bool isAlive() const override;
    void render(sf::RenderWindow& window) override;
    RenderLayer getLayer() const override;
};
