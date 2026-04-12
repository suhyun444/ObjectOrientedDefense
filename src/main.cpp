#include "GameManager.h"
#include "Renderer.h"
#include "ObjectFactory.h"
#include "Timer.h" // 앞서 언급하신 정적 타이머 클래스 가정
#include "Tile.h"

int main() {
    // 1. 시스템 매니저 스택 할당 (생명주기 안전성 확보)
    // Renderer 내부에서 sf::RenderWindow가 생성됨
    Renderer renderer(1280, 720, "Tower Defense Alpha");
    GameManager gameManager;
    Timer timer; 

    // 2. ObjectFactory 초기화 (의존성 주입)
    // 이제 팩토리는 내부적으로 gameManager와 renderer의 포인터를 가짐
    ObjectFactory::getInstance().initialize(&gameManager, &renderer);

    // 3. 초기 객체 생성 (예: 플레이어)
    auto player = ObjectFactory::getInstance().createPlayer();
    ObjectFactory::getInstance().createTile(0, 0, TileType::Buildable); // 초록
    ObjectFactory::getInstance().createTile(1, 0, TileType::Path);      // 회색
    ObjectFactory::getInstance().createTile(2, 0, TileType::Occupied);  // 빨강

    // 4. 메인 게임 루프
    while (renderer.isWindowOpen()) {
        // 타이머 업데이트 (Static 변수 deltaTime 갱신)
        timer.update();

        // 시스템 업데이트 루프
        gameManager.tick();

        // 시스템 렌더링 루프 (내부에서 정렬 및 그리기 수행)
        renderer.drawAll();
    }

    return 0;
}