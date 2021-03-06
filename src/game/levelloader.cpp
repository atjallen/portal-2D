#include "levelloader.h"

#include <fstream>

#include "game/gameobjects/ceiling.h"
#include "game/gameobjects/floor.h"
#include "game/gameobjects/player.h"
#include "game/gameobjects/wall.h"
#include "game/gameobjects/wallnocollision.h"

const float LevelLoader::TILE_SIZE = 50.0f;

LevelLoader::LevelLoader() : structureCounter(0) {}

void LevelLoader::loadLevelFile(const std::string& filename) {
    std::ifstream levelFileStream(filename);

    // Read level dimensions
    int width, height;
    levelFileStream >> width;
    levelFileStream >> height;
    levelFileStream.get();  // Advance to next line

    // Read level contents and create objects
    for (int i = 0; i < height; i++) {
        std::string line;
        std::getline(levelFileStream, line);
        for (int j = 0; j < width; j++) {
            char tile = line[j];
            switch (tile) {
                case 'C': {
                    createStructure<Ceiling>(j, i);
                    break;
                }
                case 'F': {
                    createStructure<Floor>(j, i);
                    break;
                }
                case 'N': {
                    createStructure<WallNoCollision>(j, i);
                    break;
                }
                case 'W': {
                    createStructure<Wall>(j, i);
                    break;
                }
                case 'P': {
                    createPlayer(j, i);
                    break;
                }
            }
        }
    }
}

sf::Vector2f LevelLoader::gridCoordsToGameCoords(int x, int y) {
    return sf::Vector2f(x * TILE_SIZE + TILE_SIZE / 2 + TILE_SIZE, y * TILE_SIZE + TILE_SIZE / 2 + TILE_SIZE);
}

void LevelLoader::createPlayer(int x, int y) {
    auto& player = engine::Engine::createGameObject<Player>("Player", gridCoordsToGameCoords(x, y));
}
