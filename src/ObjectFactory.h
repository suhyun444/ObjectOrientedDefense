#pragma once

#include "MonsterStats.h"
#include "MonsterStatsLoader.h"
#include "TowerDescription.h"
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class FPSCounter;
class BaseHUD;
class WaveHUD;
class Tile;
class GameManager;
class Renderer;
class InputManager;
class Base;
class Monster;
class Tower;
class BasicTower;
class GameObject;
class Projectile;
class Wave;
class WaveStartButton;
class Path;
class Map;
class TowerSelectPanel;
class TowerActionMenu;
class GoldNotice;
class GameResultPopup;
class ErrorPopup;

class ObjectFactory {
private:
    GameManager*  gameManager  = nullptr;
    Renderer*     renderer     = nullptr;
    InputManager* inputManager = nullptr;
    Base*         base         = nullptr;
    Tile*         selectedTile = nullptr;
    std::weak_ptr<TowerSelectPanel>  activeTowerPanel;
    std::weak_ptr<TowerActionMenu>   activeTowerActionMenu;
    std::weak_ptr<GoldNotice>        activeGoldNotice;
    std::shared_ptr<GameResultPopup> activeGameResultPopup;
    std::shared_ptr<ErrorPopup>      activeErrorPopup;
    MonsterStats monsterStats;

    ObjectFactory() = default;

public:
    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    void initialize(GameManager* gm, Renderer* r, InputManager* im) {
        gameManager  = gm;
        renderer     = r;
        inputManager = im;
        MonsterStatsLoader loader;
        monsterStats = loader.load("data/monster_stats.csv");
    }

    std::shared_ptr<Base>            createBase();
    std::shared_ptr<Tile>            createTile(int gridX, int gridY);
    std::shared_ptr<Monster>         createMonster(const Path* path, MonsterType type = MonsterType::Goblin);
    std::shared_ptr<Tower>           createTower(TowerType type, Tile* tile);
    std::shared_ptr<Projectile>      createProjectile(const std::shared_ptr<Monster>& target, int damage, float x, float y);
    void                             registerProjectile(const std::shared_ptr<Projectile>& projectile);
    void                             registerEffect(const std::shared_ptr<GameObject>& effect);
    std::shared_ptr<Wave>            createWave(const Path* path);
    std::shared_ptr<WaveStartButton> createWaveStartButton(Wave* wave);
    std::shared_ptr<Path>            createPath(const std::vector<sf::Vector2i>& coords);
    std::shared_ptr<Map>             createMap(int width, int height);
    std::shared_ptr<FPSCounter>      createFPSCounter();
    std::shared_ptr<BaseHUD>         createBaseHUD(const Base* base);
    std::shared_ptr<WaveHUD>         createWaveHUD(const Wave* wave);
    std::shared_ptr<TowerSelectPanel> createTowerSelectPanel(Tile* tile);
    std::shared_ptr<TowerActionMenu>  createTowerActionMenu(Tower* tower, Tile* tile);
    void                              createGoldNotice();
    void                              createGameResultPopup(bool isVictory);
    void                              createErrorPopup();
};
