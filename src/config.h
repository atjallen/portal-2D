#pragma once

#include <string>

#include <nlohmann/json.hpp>

class Config {
   public:
    static void initialise(const std::string& configFilename);

    static std::string getTextureFilename(const std::string& textureName);
    static std::string getImageFilename(const std::string& imageName);
    static std::string getFontFilename(const std::string& fontName);

   private:
    static nlohmann::json config;
};