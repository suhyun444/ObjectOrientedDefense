#pragma once

#include "MonsterDescription.h"
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>

class FPSCounter;
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

class ObjectFactory {
private:
    GameManager*  gameManager  = nullptr;
    Renderer*     renderer     = nullptr;
    InputManager* inputManager = nullptr;

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
    }

    std::shared_ptr<Player>          createPlayer();
    std::shared_ptr<Tile>            createTile(int gridX, int gridY);
    std::shared_ptr<Monster>         createMonster(const Path* path, const MonsterDescription& desc = MonsterDescription{});
    std::shared_ptr<BasicTower>      createBasicTower(float x, float y);
    std::shared_ptr<Projectile>      createProjectile(const std::shared_ptr<Monster>& target, int damage, float x, float y);
    std::shared_ptr<Wave>            createWave(const Path* path);
    std::shared_ptr<WaveStartButton> createWaveStartButton(Wave* wave);
    std::shared_ptr<Path>            createPath(const std::vector<sf::Vector2i>& coords);
    std::shared_ptr<Map>             createMap(int width, int height);
    std::shared_ptr<FPSCounter>      createFPSCounter();
};
