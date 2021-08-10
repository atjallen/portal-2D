#include "../engine/config.h"
#include "../engine/engine.h"

#include "levelloader.h"

#include "gameobjects/floor.h"
#include "gameobjects/player.h"
#include "gameobjects/portalgun.h"

#include "../util/vector.h"

int main() {
    engine::Engine::configure("config.json");

    // Load test level
    LevelLoader levelLoader;
    levelLoader.loadLevelFile(engine::Config::getLevelFilename("test"));

    // Create test portal gun and assign to player
    auto& portalGun = engine::Engine::createGameObject<PortalGun>("portalgun");
    portalGun.getComponent<engine::Transform>()->setPosition(
        sf::Vector2f(50 * 3, 50 * 3));
    engine::Engine::getGameObject<Player>("Player").setPortalGun(portalGun);

    engine::Engine::run();

    return 0;
}