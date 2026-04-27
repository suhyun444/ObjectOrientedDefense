#include "ObjectFactory.h"
#include "FPSCounter.h"
#include "Player.h"
#include "GameManager.h" 
#include "Tile.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Monster.h"
#include "BasicTower.h"
#include "Projectile.h"
#include "Wave.h"
#include "Map.h"
#include "Path.h"
#include "ProjectileDescription.h"
#include "WaveDescription.h"

std::shared_ptr<Player> ObjectFactory::createPlayer() {
    // 람다를 이용해 콜백 바인딩
    auto player = std::make_shared<Player>([this]() {
        if (this->gameManager) {
            this->gameManager->triggerGameOver();
        }
    });
    return player;
}

std::shared_ptr<Tile> ObjectFactory::createTile(int gridX, int gridY) {
    auto tile = std::make_shared<Tile>(gridX, gridY);

    if (gameManager) gameManager->addRoutine(tile);
    if (renderer) renderer->addRenderable(tile);
    if (inputManager) inputManager->addClickable(tile);

    return tile;
}

std::shared_ptr<Monster> ObjectFactory::createMonster(const Path* path) {
    auto monster = std::make_shared<Monster>();
    monster->setPath(path);

    if (gameManager) gameManager->addRoutine(monster);
    if (renderer) renderer->addRenderable(monster);

    return monster;
}

std::shared_ptr<BasicTower> ObjectFactory::createBasicTower(float x, float y) {
    auto tower = std::make_shared<BasicTower>();
    tower->setPosition(x, y);

    if (gameManager) gameManager->addRoutine(tower);
    if (renderer) renderer->addRenderable(tower);

    return tower;
}

std::shared_ptr<Projectile> ObjectFactory::createProjectile(const std::shared_ptr<Monster>& target, int damage, float x, float y) {
    ProjectileDescription projectileDescription;
    projectileDescription.damage = damage;
    auto projectile = std::make_shared<Projectile>(target, projectileDescription);
    projectile->setPosition(x, y);

    if (gameManager) gameManager->addRoutine(projectile);
    if (renderer) renderer->addRenderable(projectile);

    return projectile;
}

std::shared_ptr<Wave> ObjectFactory::createWave(int totalCount, float spawnInterval, const Path* path) {
    WaveDescription waveDescription;
    waveDescription.rewardGold = 0;
    waveDescription.waveInformation.push_back(std::make_pair(totalCount, MonsterType::Goblin));
    (void)spawnInterval;
    auto wave = std::make_shared<Wave>(waveDescription);
    wave->setPath(path);

    if (gameManager) gameManager->addRoutine(wave);

    return wave;
}

std::shared_ptr<Map> ObjectFactory::createMap(int width, int height) {
    auto map = std::make_shared<Map>(width, height);
    map->initialize(*this);

    if (renderer) renderer->addRenderable(map);

    return map;
}

std::shared_ptr<FPSCounter> ObjectFactory::createFPSCounter() {
    auto obj = std::make_shared<FPSCounter>();
    if (gameManager) gameManager->addRoutine(obj);
    if (renderer) renderer->addRenderable(obj);
    return obj;
}