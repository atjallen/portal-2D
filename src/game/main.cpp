#include "../engine/config.h"
#include "../engine/game.h"

#include "levelloader.h"

#include "gameobjects/floor.h"
#include "gameobjects/player.h"
#include "gameobjects/portalgun.h"

int main() {
    Config::initialise("config.json");
    Game::initialise();

    // Load test level
    LevelLoader levelLoader;
    levelLoader.loadLevelFile(Config::getLevelFilename("test"));

    // Create test portal gun and assign to player
    auto& portalGun = Game::create<PortalGun>("portalgun");
    portalGun.getComponent<Transform>()->setPosition(
        sf::Vector2f(50 * 3, 50 * 3));
    Game::get<Player>("Player").setPortalGun(portalGun);

    Game::run();

    return 0;
}