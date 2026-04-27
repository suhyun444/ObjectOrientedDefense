#pragma once
#include <memory>

class FPSCounter;
class Tile;
enum class TileType;
class GameManager;
class Renderer;
class Player;
class Monster;
class Tower;
class BasicTower;
class Projectile;
class Wave;
class Path;
class Map;

class ObjectFactory {
private:
    GameManager* gameManager = nullptr;
    Renderer* renderer = nullptr;

    ObjectFactory() = default; // 싱글톤

public:
    static ObjectFactory& getInstance() {
        static ObjectFactory instance;
        return instance;
    }

    // main 함수에서 딱 한 번 호출하여 매니저들을 연결
    void initialize(GameManager* gm, Renderer* r) {
        gameManager = gm;
        renderer = r;
    }

    // 타워나 몬스터가 호출할 팩토리 메서드
    std::shared_ptr<Player> createPlayer();
    std::shared_ptr<Tile> createTile(int gridX, int gridY, TileType type);
    std::shared_ptr<Monster> createMonster(const Path* path);
    std::shared_ptr<BasicTower> createBasicTower(float x, float y);
    std::shared_ptr<Projectile> createProjectile(const std::shared_ptr<Monster>& target, int damage, float x, float y);
    std::shared_ptr<Wave> createWave(int totalCount, float spawnInterval, const Path* path);
    std::shared_ptr<Map> createMap(int width, int height);
    std::shared_ptr<FPSCounter> createFPSCounter();
};