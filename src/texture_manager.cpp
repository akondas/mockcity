#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "texture_manager.hpp"

void TextureManager::load()
{
    loadTexture("background",  "media/gfx/background.png");
    loadTexture("grass",       "media/gfx/grass.png");
    loadTexture("forest",      "media/gfx/forest.png");
    loadTexture("water",       "media/gfx/water.png");
    loadTexture("residential", "media/gfx/residential.png");
    loadTexture("commercial",  "media/gfx/commercial.png");
    loadTexture("industrial",  "media/gfx/industrial.png");
    loadTexture("road",        "media/gfx/road.png");
    loadTexture("background",  "media/gfx/background.png");
}

void TextureManager::loadTexture(const std::string &name, const std::string &filename)
{
    sf::Texture texture;
    texture.loadFromFile(filename);

    textures[name] = texture;
}

sf::Texture &TextureManager::getRef(const std::string &texture)
{
    return textures.at(texture);
}
