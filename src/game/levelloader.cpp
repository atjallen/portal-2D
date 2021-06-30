#include "levelloader.h"

#include <fstream>

#include "gameobjects/ceiling.h"
#include "gameobjects/floor.h"
#include "gameobjects/player.h"
#include "gameobjects/wall.h"
#include "gameobjects/wallnocollision.h"

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
    return sf::Vector2f(x * TILE_SIZE + TILE_SIZE / 2 + TILE_SIZE,
                        y * TILE_SIZE + TILE_SIZE / 2 + TILE_SIZE);
}

void LevelLoader::createPlayer(int x, int y) {
    auto& player = Engine::createGameObject<Player>("Player");
    player.getComponent<Transform>()->setPosition(gridCoordsToGameCoords(x, y));
}
