#pragma once

#include "gameobjectmanager.h"

#include <string>

#include "components/transform.h"

class LevelLoader {
   public:
    static const float TILE_SIZE;

    LevelLoader(GameObjectManager& gameObjectManager);

    void loadLevelFile(const std::string& filename);

   private:
    GameObjectManager& gom;
    int structureCounter;

    sf::Vector2f gridCoordsToGameCoords(int x, int y);

    void createPlayer(int x, int y);
    template <typename StructureType>
    void createStructure(int x, int y);
};

template <typename StructureType>
inline void LevelLoader::createStructure(int x, int y) {
    auto& structure = gom.create<StructureType>(
        "Structure" + std::to_string(structureCounter++));
    structure.setDimensions(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    structure.getComponent<Transform>()->setPosition(
        gridCoordsToGameCoords(x, y));
}
