#include "config.h"

#include <fstream>

namespace engine {

nlohmann::json Config::config;

void Config::initialise(const std::string& configFilename) {
    std::ifstream configFileStream(configFilename);
    configFileStream >> config;
}

std::string Config::getTextureFilename(const std::string& textureName) {
    return config["resources"]["textures"][textureName].get<std::string>();
}

std::string Config::getImageFilename(const std::string& imageName) {
    return config["resources"]["images"][imageName].get<std::string>();
}

std::string Config::getFontFilename(const std::string& fontName) {
    return config["resources"]["fonts"][fontName].get<std::string>();
}

std::string Config::getLevelFilename(const std::string& levelName) {
    return config["resources"]["levels"][levelName].get<std::string>();
}

}  // namespace engine
