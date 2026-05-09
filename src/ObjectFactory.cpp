#include "ObjectFactory.h"
#include "FPSCounter.h"
#include "BaseHUD.h"
#include "WaveHUD.h"
#include "Base.h"
#include "GameManager.h"
#include "Tile.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Monster.h"
#include "BasicTower.h"
#include "IceTower.h"
#include "SniperTower.h"
#include "ExplosionTower.h"
#include "Projectile.h"
#include "NormalProjectile.h"
#include "Wave.h"
#include "WaveStartButton.h"
#include "Map.h"
#include "Path.h"
#include "TowerSelectPanel.h"
#include "TowerActionMenu.h"
#include "GoldNotice.h"
#include "GameResultPopup.h"
#include "ErrorPopup.h"

std::shared_ptr<Base> ObjectFactory::createBase() {
    auto p = std::make_shared<Base>([this]() {
        if (gameManager) gameManager->triggerGameOver();
        createGameResultPopup(false);
    });
    if (gameManager) gameManager->setBase(p.get());
    base = p.get();
    return p;
}

std::shared_ptr<Tile> ObjectFactory::createTile(int gridX, int gridY) {
    auto tile = std::make_shared<Tile>(gridX, gridY);

    tile->onBuildRequest = [this](Tile* t) {
        if (auto panel = activeTowerPanel.lock()) panel->kill();
        if (auto menu  = activeTowerActionMenu.lock()) menu->kill();
        if (selectedTile) selectedTile->setHighlighted(false);

        selectedTile = t;
        t->setHighlighted(true);
        activeTowerPanel = createTowerSelectPanel(t);
    };

    tile->onTowerClick = [this](Tower* tw, Tile* t) {
        if (auto panel = activeTowerPanel.lock()) panel->kill();
        if (auto menu  = activeTowerActionMenu.lock()) menu->kill();
        if (selectedTile) { selectedTile->setHighlighted(false); selectedTile = nullptr; }
        activeTowerActionMenu = createTowerActionMenu(tw, t);
    };

    if (gameManager)  gameManager->addRoutine(tile);
    if (renderer)     renderer->addRenderable(tile);
    if (inputManager) inputManager->addClickable(tile);

    return tile;
}

std::shared_ptr<Monster> ObjectFactory::createMonster(const Path* path, MonsterType type) {
    MonsterDescription desc = monsterStats.get(type);

    auto monster = std::make_shared<Monster>(desc);
    monster->setPath(path);
    if (gameManager) {
        monster->setOnReachedEnd([gm = gameManager]() { gm->dealDamageToBase(1); });
        monster->setOnDefeated([gm = gameManager, gold = desc.rewardGold]() { gm->addGoldToBase(gold); });
        gameManager->addRoutine(monster);
    }
    if (renderer) renderer->addRenderable(monster);

    return monster;
}

std::shared_ptr<Tower> ObjectFactory::createTower(TowerType type, Tile* tile) {
    std::shared_ptr<Tower> tower;
    switch (type) {
        case TowerType::Basic:     tower = std::make_shared<BasicTower>();     break;
        case TowerType::Ice:       tower = std::make_shared<IceTower>();       break;
        case TowerType::Sniper:    tower = std::make_shared<SniperTower>();    break;
        case TowerType::Explosion: tower = std::make_shared<ExplosionTower>(); break;
        default:                   tower = std::make_shared<BasicTower>();     break;
    }
    auto pos = tile->getPosition();
    tower->setPosition(pos.x, pos.y);
    tower->setGridPosition({ tile->getGridX(), tile->getGridY() });
    if (gameManager)
        tower->setMonstersProvider([gm = gameManager] { return gm->getAliveMonsters(); });

    if (gameManager) gameManager->addRoutine(tower);
    if (renderer)    renderer->addRenderable(tower);

    return tower;
}

std::shared_ptr<TowerSelectPanel> ObjectFactory::createTowerSelectPanel(Tile* tile) {
    auto panel = std::make_shared<TowerSelectPanel>(tile, inputManager);

    panel->onClose = [this, tile]() {
        tile->setHighlighted(false);
        selectedTile = nullptr;
    };

    panel->onSelectTower = [this, tile](TowerType type, int cost) {
        if (!base || !base->useGold(cost)) {
            createGoldNotice();
            return false;
        }
        auto tower = createTower(type, tile);
        tile->setTower(tower.get());
        tile->setHighlighted(false);
        selectedTile = nullptr;
        return true;
    };

    if (gameManager)  gameManager->addRoutine(panel);
    if (renderer)     renderer->addRenderable(panel);
    if (inputManager) inputManager->addClickable(panel);

    return panel;
}

std::shared_ptr<TowerActionMenu> ObjectFactory::createTowerActionMenu(Tower* tower, Tile* tile) {
    auto menu = std::make_shared<TowerActionMenu>(tower, tile, inputManager);

    menu->onUpgrade = [this, tower]() {
        if (!base || !base->useGold(tower->getDescription().upgradeCost)) {
            createGoldNotice();
            return;
        }
        tower->upgrade();
    };

    menu->onRemove = [this, tower, tile]() {
        if (base) base->addGold(tower->getRefundGold());
        tile->setTower(nullptr);
        tower->kill();
    };

    if (gameManager)  gameManager->addRoutine(menu);
    if (renderer)     renderer->addRenderable(menu);
    if (inputManager) inputManager->addClickable(menu);

    return menu;
}

void ObjectFactory::createGameResultPopup(bool isVictory) {
    if (!renderer) return;
    auto popup = std::make_shared<GameResultPopup>(isVictory, renderer->getWindow(), [this]() {
        if (renderer) renderer->getWindow().close();
    });
    activeGameResultPopup = popup;
    renderer->addRenderable(popup);
    if (inputManager) inputManager->addPriorityClickable(popup);
}

void ObjectFactory::createErrorPopup() {
    if (!renderer) return;
    auto popup = std::make_shared<ErrorPopup>(renderer->getWindow(), [this]() {
        if (renderer) renderer->getWindow().close();
    });
    activeErrorPopup = popup;
    renderer->addRenderable(popup);
    if (inputManager) inputManager->addPriorityClickable(popup);
}

void ObjectFactory::createGoldNotice() {
    if (auto existing = activeGoldNotice.lock()) existing->kill();
    auto notice = std::make_shared<GoldNotice>();
    activeGoldNotice = notice;
    if (gameManager) gameManager->addRoutine(notice);
    if (renderer)    renderer->addRenderable(notice);
}

std::shared_ptr<Projectile> ObjectFactory::createProjectile(const std::shared_ptr<Monster>& target, int damage, float x, float y) {
    auto projectile = std::make_shared<NormalProjectile>(target, damage);
    projectile->setPosition(x, y);
    registerProjectile(projectile);
    return projectile;
}

void ObjectFactory::registerProjectile(const std::shared_ptr<Projectile>& projectile) {
    if (gameManager) gameManager->addRoutine(projectile);
    if (renderer)    renderer->addRenderable(projectile);
}

void ObjectFactory::registerEffect(const std::shared_ptr<GameObject>& effect) {
    if (gameManager) gameManager->addRoutine(effect);
    if (renderer)    renderer->addRenderable(effect);
}


std::shared_ptr<Wave> ObjectFactory::createWave(const Path* path) {
    auto wave = std::make_shared<Wave>(path);

    if (gameManager) {
        wave->setOnComplete([gm = gameManager](int gold) { gm->addGoldToBase(gold); });
        wave->setOnVictory([this]() {
            if (gameManager) gameManager->triggerVictory();
            createGameResultPopup(true);
        });
        gameManager->addRoutine(wave);
    }

    return wave;
}

std::shared_ptr<WaveStartButton> ObjectFactory::createWaveStartButton(Wave* wave) {
    auto button = std::make_shared<WaveStartButton>(wave);

    if (gameManager) gameManager->addRoutine(button);
    if (renderer)    renderer->addRenderable(button);
    if (inputManager) inputManager->addClickable(button);

    return button;
}

std::shared_ptr<Path> ObjectFactory::createPath(const std::vector<sf::Vector2i>& coords) {
    auto path = std::make_shared<Path>();
    path->setPathTiles(coords);
    if (renderer) renderer->addRenderable(path);
    return path;
}

std::shared_ptr<Map> ObjectFactory::createMap(int width, int height) {
    return std::make_shared<Map>(width, height);
}

std::shared_ptr<FPSCounter> ObjectFactory::createFPSCounter() {
    auto obj = std::make_shared<FPSCounter>();
    if (gameManager) gameManager->addRoutine(obj);
    if (renderer)    renderer->addRenderable(obj);
    return obj;
}

std::shared_ptr<BaseHUD> ObjectFactory::createBaseHUD(const Base* base) {
    auto hud = std::make_shared<BaseHUD>(base);
    if (renderer) renderer->addRenderable(hud);
    return hud;
}

std::shared_ptr<WaveHUD> ObjectFactory::createWaveHUD(const Wave* wave) {
    auto hud = std::make_shared<WaveHUD>(wave);
    if (renderer) renderer->addRenderable(hud);
    return hud;
}
