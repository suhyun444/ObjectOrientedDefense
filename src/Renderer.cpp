#include "Renderer.h"
#include <algorithm>

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title) 
    : window(sf::VideoMode({width, height}), title, sf::Style::Titlebar | sf::Style::Close) {}

sf::RenderWindow& Renderer::getWindow() {
    return window;
}

bool Renderer::isWindowOpen() const {
    return window.isOpen();
}

void Renderer::addRenderable(std::weak_ptr<IRenderable> renderable) {
    renderables.push_back(renderable);
}

void Renderer::drawAll() {
    // 화면 초기화
    window.clear(sf::Color(188, 188, 188));

    // 2. 유효한 객체들만 임시 벡터에 모으고 + 죽은(Expired) weak_ptr 삭제
    std::vector<std::shared_ptr<IRenderable>> validObjects;
    
    for (auto it = renderables.begin(); it != renderables.end(); ) {
        // .lock()은 weak_ptr가 가리키는 객체가 살아있으면 shared_ptr를 반환, 죽었으면 nullptr 반환
        if (auto shared = it->lock()) {
            validObjects.push_back(shared);
            ++it;
        } else {
            // 객체가 소멸되었다면(Expired), 렌더러 배열에서도 삭제
            it = renderables.erase(it);
        }
    }

    // 3. Z-Index(Layer) 기준으로 정렬 (람다 함수 사용)
    std::sort(validObjects.begin(), validObjects.end(), 
        [](const std::shared_ptr<IRenderable>& a, const std::shared_ptr<IRenderable>& b) {
            return static_cast<int>(a->getLayer()) < static_cast<int>(b->getLayer());
        }
    );

    // 4. 정렬된 순서대로 그리기
    for (auto& obj : validObjects) {
        obj->render(window);
    }

    // 화면 표시
    window.display();
}