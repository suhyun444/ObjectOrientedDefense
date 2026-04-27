#include "GameManager.h"
#include "Renderer.h"
#include "ObjectFactory.h"
#include "Tile.h"
#include "Time.h"
#include "Map.h"
#include "Wave.h"
#include "InputManager.h"

int main() {
    // 1. 시스템 매니저 스택 할당 (생명주기 안전성 확보)
    // Renderer 내부에서 sf::RenderWindow가 생성됨
    Renderer renderer(1280, 720, "Tower Defense Alpha");
    GameManager gameManager;
    Time time; // 게임 전체에서 공유되는 시간 관리 객체
    InputManager inputManager(renderer.getWindow());
    // 2. ObjectFactory 초기화 (의존성 주입)
    // 이제 팩토리는 내부적으로 gameManager와 renderer의 포인터를 가짐
    ObjectFactory::getInstance().initialize(&gameManager, &renderer);
    ObjectFactory::getInstance().createFPSCounter();

    ObjectFactory::getInstance().initialize(&gameManager, &renderer, &inputManager);

    auto player = ObjectFactory::getInstance().createPlayer();
    auto map = ObjectFactory::getInstance().createMap(26, 15);

    while (renderer.isWindowOpen()) {
        inputManager.processInput();
        time.update();
        gameManager.tick();
        renderer.drawAll();
    }

    return 0;
}
