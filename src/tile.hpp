#ifndef TILE_HPP
#define TILE_HPP

#include <cstdint>
#include <SFML/Graphics.hpp>
#include <vector>

#include "animation_handler.hpp"

enum class TileType {
    VOID,
    GRASS,
    FOREST,
    WATER,
    RESIDENTIAL,
    COMMERCIAL,
    INDUSTRIAL,
    ROAD
};

std::string tileTypeToStr(TileType type);

class Tile {
public:
    Tile() {}

    AnimationHandler animHandler;
    sf::Sprite sprite;

    TileType tileType;

    // TODO: Resize to proper (smaller) types
    uint32_t tileVariant;
    uint32_t regions[1];
    uint32_t cost;
    uint32_t maxPopPerLevel;
    uint32_t maxLevels;
    uint32_t population;
    uint32_t production;

    uint64_t storedGoods;

    Tile(uint32_t tileSize, uint32_t height, sf::Texture &texture, const std::vector<Animation> &animations,
        const TileType tileType, uint32_t cost, uint32_t maxPopPerLevel, uint32_t maxLevels)
    {
        this->tileType = tileType;
        this->tileVariant = 0;
        this->regions[0] = 0;

        this->cost = cost;
        this->population = 0;
        this->maxPopPerLevel = maxPopPerLevel;
        this->maxLevels = maxLevels;
        this->production = 0;
        this->storedGoods = 0;

        this->sprite.setOrigin(sf::Vector2f(0.0f, tileSize * (height - 1)));
        this->sprite.setTexture(texture);
        this->animHandler.frameSize = sf::IntRect(0, 0, tileSize * 2, tileSize * height);
        for (auto animation : animations) {
            this->animHandler.addAnim(animation);
        }
        this->animHandler.update(0.0f);
    }

    void draw(sf::RenderWindow &window, float dt);

    void update();

    std::string getCost() {
        return std::to_string(this->cost);
    }
};

#endif /* TILE_HPP */
