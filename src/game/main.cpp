#include "../engine/config.h"
#include "../engine/engine.h"

#include "levelloader.h"

#include "gameobjects/floor.h"
#include "gameobjects/player.h"
#include "gameobjects/portalgun.h"

int main() {
    Config::initialise("config.json");
    Engine::initialise();

    // Load test level
    LevelLoader levelLoader;
    levelLoader.loadLevelFile(Config::getLevelFilename("test"));

    // Create test portal gun and assign to player
    auto& portalGun = Engine::create<PortalGun>("portalgun");
    portalGun.getComponent<Transform>()->setPosition(
        sf::Vector2f(50 * 3, 50 * 3));
    Engine::get<Player>("Player").setPortalGun(portalGun);

    Engine::run();

    return 0;
}