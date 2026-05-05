#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <vector>
#include "IClickable.h"

class InputManager {
private:
    sf::RenderWindow& window;
    std::vector<std::weak_ptr<IClickable>> clickables;

public:
    explicit InputManager(sf::RenderWindow& window);

    void addClickable(const std::shared_ptr<IClickable>& clickable);
    void addPriorityClickable(const std::shared_ptr<IClickable>& clickable);
    void clearClickables();

    sf::Vector2i getMousePosition() const;

    void processInput();
    bool handleEvent(const sf::Event& event);
};
