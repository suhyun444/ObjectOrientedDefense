#include "ObjectFactory.h"
#include "Player.h"      
#include "GameManager.h" 
#include "Tile.h"
#include "Renderer.h"

std::shared_ptr<Player> ObjectFactory::createPlayer() {
    // 람다를 이용해 콜백 바인딩
    auto player = std::make_shared<Player>([this]() {
        if (this->gameManager) {
            this->gameManager->triggerGameOver();
        }
    });

    // GameManager에 자동 등록
    if (gameManager) {
        gameManager->addRoutine(player);
    }

    return player;
}
std::shared_ptr<Tile> ObjectFactory::createTile(int gridX, int gridY, TileType type) {
    auto tile = std::make_shared<Tile>(gridX, gridY, type);
    
    if (gameManager) gameManager->addRoutine(tile);
    if (renderer) renderer->addRenderable(tile);
    
    return tile;
}