#include "ObjectFactory.h"
#include "Player.h"      
#include "GameManager.h" 

std::shared_ptr<Player> ObjectFactory::createPlayer(GameManager& gameManager) {
    // 람다를 이용해 콜백 바인딩
    auto player = std::make_shared<Player>([&gameManager]() {
        gameManager.triggerGameOver();
    });

    // GameManager에 자동 등록
    gameManager.addRoutine(player);

    return player;
}