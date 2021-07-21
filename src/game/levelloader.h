#pragma once

#include <string>

#include "../engine/components/transform.h"
#include "../engine/engine.h"

class LevelLoader {
   public:
    static const float TILE_SIZE;

    LevelLoader();

    void loadLevelFile(const std::string& filename);

   private:
    int structureCounter;

    sf::Vector2f gridCoordsToGameCoords(int x, int y);

    void createPlayer(int x, int y);
    template <typename StructureType>
    void createStructure(int x, int y);
};

template <typename StructureType>
inline void LevelLoader::createStructure(int x, int y) {
    auto& structure = engine::Engine::createGameObject<StructureType>(
        "Structure" + std::to_string(structureCounter++));
    structure.setDimensions(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    structure.getComponent<engine::Transform>()->setPosition(
        gridCoordsToGameCoords(x, y));
}
