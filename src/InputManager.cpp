#include "InputManager.h"

InputManager::InputManager(sf::RenderWindow& window) : window(window) {}

sf::Vector2i InputManager::getMousePosition() const {
    return sf::Mouse::getPosition(window);
}

void InputManager::addClickable(const std::shared_ptr<IClickable>& clickable) {
    if (!clickable) {
        return;
    }
    clickables.push_back(clickable);
}

void InputManager::clearClickables() {
    clickables.clear();
}

void InputManager::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            continue;
        }

        handleEvent(event);
    }
}

bool InputManager::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonReleased) {
        return false;
    }

    if (event.mouseButton.button != sf::Mouse::Button::Left) {
        return false;
    }

    const sf::Vector2i mousePixel(event.mouseButton.x, event.mouseButton.y);

    for (auto it = clickables.begin(); it != clickables.end();) {
        auto clickable = it->lock();
        if (!clickable) {
            it = clickables.erase(it);
            continue;
        }

        ++it;

        if (!clickable->isEnabled()) {
            continue;
        }

        if (!clickable->containsPoint(mousePixel)) {
            continue;
        }

        if (clickable->onClick()) {
            return true;
        }
    }

    return false;
}
