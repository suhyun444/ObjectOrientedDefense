#include "GameManager.h"
#include "Renderer.h"
#include "ObjectFactory.h"
#include "Timer.h" // 앞서 언급하신 정적 타이머 클래스 가정
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
    Timer timer; 
    Time time; // 게임 전체에서 공유되는 시간 관리 객체
    InputManager inputManager(renderer.getWindow());
    // 2. ObjectFactory 초기화 (의존성 주입)
    // 이제 팩토리는 내부적으로 gameManager와 renderer의 포인터를 가짐
    ObjectFactory::getInstance().initialize(&gameManager, &renderer);

    // 3. 초기 객체 생성 (예: 플레이어)
    auto player = ObjectFactory::getInstance().createPlayer();
    auto map = ObjectFactory::getInstance().createMap(26, 15);
    auto wave = ObjectFactory::getInstance().createWave(5, 1.2f, &map->getPath());
    wave->setTimer(&timer);
    wave->setSpawnDelay(1.2f);
    wave->loadFromFile("data/waves_stub.json");
std::vector<std::pair<int, int>> pathCoordinates = {
    // 0. 새로 추가된 왼쪽 진입로 (가로 4칸)
    {0,6}, {1,6}, {2,6}, {3,6},

    // 1. 원래 왼쪽에서 진입 (가로) -> 기존 대비 X + 4
    {4,6}, {5,6}, {6,6}, {7,6},
    
    // 2. 위로 꺾임 (세로)
    {7,5}, {7,4}, {7,3}, {7,2},{7,1},
    
    // 3. 오른쪽으로 꺾임 (가로)
    {8,1},{9,1}, {10,1}, {11,1}, {12,1},
    
    // 4. 아래로 깊게 꺾임 (세로)
    {12,2}, {12,3}, {12,4}, {12,5}, {12,6}, {12,7}, {12,8},
    
    // 5. 왼쪽으로 꺾임 (가로)
    {11,8}, {10,8}, {9,8}, {8,8}, {7,8},
    
    // 6. 아래로 꺾임 (세로)
    {7,9},{7,10}, {7,11}, {7,12}, {7,13},
    
    // 7. 오른쪽으로 길게 꺾임 - 하단 가로지르기 (가로)
    {8,13}, {9,13}, {10,13}, {11,13}, {12,13}, {13,13}, {14,13}, {15,13}, {16,13}, {17,13}, {18,13}, {19,13},
    
    // 8. 위로 꺾임 (세로)
    {19,12}, {19,11}, {19,10}, {19,9},{19,8},
    
    // 9. 왼쪽으로 꺾임 (가로)
    {18,8}, {17,8}, {16,8},{15,8},
    
    // 10. 위로 꺾임 (세로)
    {15,7}, {15,6}, {15,5}, {15,4},{15,3},
    
    // 11. 오른쪽으로 꺾임 (가로)
    {16,3},{17,3}, {18,3}, {19,3}, {20,3}, {21,3},
    
    // 12. 위로 꺾여서 퇴장 (세로)
    {21,2}, {21,1}, {21,0}
};

// 팩토리를 통한 임시 일괄 등록 (테스트용)
for (const auto& [x, y] : pathCoordinates) {
    ObjectFactory::getInstance().createTile(x, y, TileType::Path);
}

    // 4. 메인 게임 루프
    while (renderer.isWindowOpen()) {

        inputManager.processInput();

        time.update(); // 프레임마다 시간 갱신
        // 시스템 업데이트 루프
        gameManager.tick();

        // 시스템 렌더링 루프 (내부에서 정렬 및 그리기 수행)
        renderer.drawAll();
    }

    return 0;
}