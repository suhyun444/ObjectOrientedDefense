#include "GameManager.h"
#include "Renderer.h"
#include "ObjectFactory.h"
#include "Tile.h"
#include "Time.h"
#include "Map.h"
#include "WaveStartButton.h"
#include "InputManager.h"

int main() {
    Renderer renderer(1530, 750, "Tower Defense Alpha");
    GameManager gameManager;
    Time time;
    InputManager inputManager(renderer.getWindow());

    ObjectFactory::getInstance().initialize(&gameManager, &renderer, &inputManager);
    ObjectFactory::getInstance().createFPSCounter();

    auto player = ObjectFactory::getInstance().createPlayer();
    auto map    = ObjectFactory::getInstance().createMap(26, 15);
    auto wave      = ObjectFactory::getInstance().createWave(&map->getPath());
    auto playerHud  = ObjectFactory::getInstance().createPlayerHUD(player.get());
    auto waveHud    = ObjectFactory::getInstance().createWaveHUD(wave.get());


    while (renderer.isWindowOpen()) {
        inputManager.processInput();
        time.update();
        gameManager.tick();
        renderer.drawAll();
    }

    return 0;
}
