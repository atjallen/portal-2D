#include "engine/config.h"
#include "engine/engine.h"

#include "game/levelloader.h"

#include "game/gameobjects/floor.h"
#include "game/gameobjects/player.h"
#include "game/gameobjects/portal.h"
#include "game/gameobjects/portalgun.h"

#include "util/vector.h"

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