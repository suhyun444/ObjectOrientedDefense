#include <SFML/Graphics.hpp>
#include <optional> // SFML 3의 pollEvent 반환값 처리를 위해 필요

int main()
{
    // [변경점 1] VideoMode 초기화
    // SFML 3에서는 폭과 높이를 개별 인자로 받지 않고 sf::Vector2u 객체 하나로 받습니다. 
    // 따라서 중괄호 {} 를 사용하여 전달해야 합니다.
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "SFML 3.0.2 Window");
    while (window.isOpen())
    {
        // [변경점 2] 이벤트 루프 (std::optional 및 std::variant 적용)
        // pollEvent()는 이제 이벤트를 참조로 채우지 않고, std::optional<sf::Event>를 반환합니다.
        while (const std::optional event = window.pollEvent())
        {
            // 타입 안전(Type-safe) 방식으로 이벤트 종류를 판별합니다.
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            // (참고) 키보드 입력 등 데이터가 포함된 이벤트를 처리할 때는 getIf<T>()를 사용합니다.
            /*
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
            */
        }

        sf::CircleShape shape(3.f);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(2.f);
        shape.setFillColor(sf::Color::Black);
        shape.setPosition({640.0f,360.0f});

        window.clear();
        
        window.draw(shape); 

        window.display();
    }

    return 0;
}