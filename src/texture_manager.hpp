#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

class TextureManager
{
    public:

        TextureManager() = default;

        void load();

        sf::Texture &getRef(const std::string &texture);

    private:
        void loadTexture(const std::string &name, const std::string &filename);

        std::map<const std::string, sf::Texture> textures;
};

#endif /* TEXTURE_MANAGER_HPP */
