#pragma once

#include "MonsterDescription.h"
#include "MonsterStatsLoader.h"
#include "TowerDescription.h"
#include <map>
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class FPSCounter;
class PlayerHUD;
class WaveHUD;
class Tile;
class GameManager;
class Renderer;
class InputManager;
class Player;
class Monster;
class Tower;
class BasicTower;
class Projectile;
class Wave;
class WaveStartButton;
class Path;
class Map;
class TowerSelectPanel;
class TowerActionMenu;

class ObjectFactory {
private:
    GameManager*  gameManager  = nullptr;
    Renderer*     renderer     = nullptr;
    InputManager* inputManager = nullptr;
    Player*       player       = nullptr;
    Tile*         selectedTile = nullptr;
    std::weak_ptr<TowerSelectPanel>  activeTowerPanel;
    std::weak_ptr<TowerActionMenu>   activeTowerActionMenu;
    std::map<MonsterType, MonsterDescription> monsterStats;

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

    std::shared_ptr<Player>          createPlayer();
    std::shared_ptr<Tile>            createTile(int gridX, int gridY);
    std::shared_ptr<Monster>         createMonster(const Path* path, MonsterType type = MonsterType::Goblin);
    std::shared_ptr<Tower>           createTower(TowerType type, Tile* tile);
    std::shared_ptr<Projectile>      createProjectile(const std::shared_ptr<Monster>& target, int damage, float x, float y);
    std::shared_ptr<Wave>            createWave(const Path* path);
    std::shared_ptr<WaveStartButton> createWaveStartButton(Wave* wave);
    std::shared_ptr<Path>            createPath(const std::vector<sf::Vector2i>& coords);
    std::shared_ptr<Map>             createMap(int width, int height);
    std::shared_ptr<FPSCounter>      createFPSCounter();
    std::shared_ptr<PlayerHUD>       createPlayerHUD(const Player* player);
    std::shared_ptr<WaveHUD>         createWaveHUD(const Wave* wave);
    std::shared_ptr<TowerSelectPanel> createTowerSelectPanel(Tile* tile);
    std::shared_ptr<TowerActionMenu>  createTowerActionMenu(Tower* tower, Tile* tile);
};
