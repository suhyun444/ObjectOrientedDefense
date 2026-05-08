#pragma once
#include "IRoutine.h"
#include "IRenderable.h"
#include <SFML/System/Vector2.hpp>

// 객체 식별을 위한 태그 열거형
enum class Tag {
    Default,
    Base,
    Monster,
    Tower,
    Projectile,
    Tile
};

class GameObject : public IRoutine, public IRenderable {
protected:
    sf::Vector2f position;
    Tag tag;

public:
    GameObject(Tag tag = Tag::Default) 
        : position(0.f, 0.f), tag(tag) {}
    
    virtual ~GameObject() = default;

    // 공통 속성 제어
    void setPosition(float x, float y) { position = {x, y}; }
    sf::Vector2f getPosition() const { return position; }
    
    Tag getTag() const { return tag; }

    // 인터페이스 함수들은 자식 클래스에서 구현하도록 순수 가상 함수로 유지하거나 
    // 기본 구현을 제공할 수 있습니다.
};