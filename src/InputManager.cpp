#include "InputManager.h"
#include <optional>

InputManager::InputManager(sf::RenderWindow& window) : window(window) {}

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
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            continue;
        }

        handleEvent(*event);
    }
}

bool InputManager::handleEvent(const sf::Event& event) {

    const auto* released = event.getIf<sf::Event::MouseButtonReleased>();
    if (!released) {
        return false;
    }

    if (released->button != sf::Mouse::Button::Left) {
        return false;
    }

    const sf::Vector2i mousePixel = released->position;

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
