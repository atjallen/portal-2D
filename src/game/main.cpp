#include "../engine/config.h"
#include "../engine/engine.h"

#include "levelloader.h"

#include "gameobjects/floor.h"
#include "gameobjects/player.h"
#include "gameobjects/portal.h"
#include "gameobjects/portalgun.h"

#include "../util/vector.h"

int main() {
    engine::Engine::configure("config.json");

    // Load test level
    LevelLoader levelLoader;
    levelLoader.loadLevelFile(engine::Config::getLevelFilename("test"));

    // Create portal gun and assign to player
    auto& portalGun = engine::Engine::createGameObject<PortalGun>("portalgun");
    engine::Engine::getGameObject<Player>("Player").setPortalGun(portalGun);

    engine::Engine::run();

    return 0;
}