#include "map.hpp"
#include "inmemoryfile.hpp"

void Map::load(const std::string &filename, unsigned int width, unsigned int height, std::map<std::string, Tile> &tileAtlas)
{
    this->width = width;
    this->height = height;

    InMemoryFile file(filename);
    for (int pos = 0; pos < this->width * this->height; ++pos) {
        this->resources.push_back(255);

        switch (static_cast<TileType>(file.read<uint8_t>())) {
            default:
            case TileType::VOID:
            case TileType::GRASS:
                this->tiles.push_back(tileAtlas.at("grass"));
                break;
            case TileType::FOREST:
                this->tiles.push_back(tileAtlas.at("forest"));
                break;
            case TileType::WATER:
                this->tiles.push_back(tileAtlas.at("water"));
                break;
            case TileType::RESIDENTIAL:
                this->tiles.push_back(tileAtlas.at("residential"));
                break;
            case TileType::COMMERCIAL:
                this->tiles.push_back(tileAtlas.at("commercial"));
                break;
            case TileType::INDUSTRIAL:
                this->tiles.push_back(tileAtlas.at("industrial"));
                break;
            case TileType::ROAD:
                this->tiles.push_back(tileAtlas.at("road"));
                break;
        }

        Tile &tile = this->tiles.back();
        tile.tileVariant = file.read<uint32_t>();
        tile.regions[0] = file.read<uint32_t>();
        tile.population = file.read<uint32_t>();
        tile.storedGoods = file.read<uint64_t>();
    }
}

void Map::save(const std::string &filename)
{
    InMemoryFile file;
    for (const auto &tile : tiles) {
        file.write<>(static_cast<uint8_t>(tile.tileType));
        file.write<>(tile.tileVariant);
        file.write<>(tile.regions[0]);
        file.write<>(tile.population);
        file.write<>(tile.storedGoods);
    }

    file.save(filename);
}

void Map::draw(sf::RenderWindow &window, float dt) {
    sf::Vector2f pos;

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
            pos.y = (x + y) * this->tileSize * 0.5;
            this->tiles[y * this->width + x].sprite.setPosition(pos);
            this->tiles[y * this->width + x].draw(window, dt);
        }
    }
}

void Map::updateDirection(TileType tileType) {
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            int pos = y * this->width + x;

            if (this->tiles[pos].tileType != tileType) continue;

            bool adjacentTiles[3][31] = {{0, 0},
                                        {0, 0},
                                        {0, 0}};

            if (x > 0 && y > 0)
                adjacentTiles[0][0] = (this->tiles[(y - 1) * this->width + (x - 1)].tileType == tileType);
            if (y > 0)
                adjacentTiles[0][3] = (this->tiles[(y - 1) * this->width + (x)].tileType == tileType);
            if (x < this->width - 1 && y > 0)
                adjacentTiles[0][4] = (this->tiles[(y - 1) * this->width + (x + 1)].tileType == tileType);
            if (x > 0)
                adjacentTiles[1][0] = (this->tiles[(y) * this->width + (x - 1)].tileType == tileType);
            if (x < width - 1)
                adjacentTiles[1][5] = (this->tiles[(y) * this->width + (x + 1)].tileType == tileType);
            if (x > 0 && y < this->height - 1)
                adjacentTiles[2][0] = (this->tiles[(y + 1) * this->width + (x - 1)].tileType == tileType);
            if (y < this->height - 1)
                adjacentTiles[2][6] = (this->tiles[(y + 1) * this->width + (x)].tileType == tileType);
            if (x < this->width - 1 && y < this->height - 1)
                adjacentTiles[2][7] = (this->tiles[(y + 1) * this->width + (x + 1)].tileType == tileType);

            if (adjacentTiles[1][0] && adjacentTiles[1][8] && adjacentTiles[0][9] && adjacentTiles[2][10])
                this->tiles[pos].tileVariant = 2;
            else if (adjacentTiles[1][0] && adjacentTiles[1][11] && adjacentTiles[0][12])
                this->tiles[pos].tileVariant = 7;
            else if (adjacentTiles[1][0] && adjacentTiles[1][13] && adjacentTiles[2][14])
                this->tiles[pos].tileVariant = 8;
            else if (adjacentTiles[0][15] && adjacentTiles[2][16] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 9;
            else if (adjacentTiles[0][16] && adjacentTiles[2][17] && adjacentTiles[1][18])
                this->tiles[pos].tileVariant = 10;
            else if (adjacentTiles[1][0] && adjacentTiles[1][19])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[0][20] && adjacentTiles[2][21])
                this->tiles[pos].tileVariant = 1;
            else if (adjacentTiles[2][22] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 3;
            else if (adjacentTiles[0][23] && adjacentTiles[1][24])
                this->tiles[pos].tileVariant = 4;
            else if (adjacentTiles[1][0] && adjacentTiles[0][25])
                this->tiles[pos].tileVariant = 5;
            else if (adjacentTiles[2][26] && adjacentTiles[1][27])
                this->tiles[pos].tileVariant = 6;
            else if (adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[1][28])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[0][29])
                this->tiles[pos].tileVariant = 1;
            else if (adjacentTiles[2][30])
                this->tiles[pos].tileVariant = 1;
        }
    }
}

void Map::depthfirstsearch(std::vector<TileType> &whitelist,
                           sf::Vector2i pos, int label, int regionType = 0) {
    if (pos.x < 0 || pos.x >= this->width) return;
    if (pos.y < 0 || pos.y >= this->height) return;
    if (this->tiles[pos.y * this->width + pos.x].regions[regionType] != 0) return;
    bool found = false;
    for (auto type : whitelist) {
        if (type == this->tiles[pos.y * this->width + pos.x].tileType) {
            found = true;
            break;
        }
    }
    if (!found) return;

    this->tiles[pos.y * this->width + pos.x].regions[regionType] = label;

    depthfirstsearch(whitelist, pos + sf::Vector2i(-1, 0), label, regionType);
    depthfirstsearch(whitelist, pos + sf::Vector2i(0, 1), label, regionType);
    depthfirstsearch(whitelist, pos + sf::Vector2i(1, 0), label, regionType);
    depthfirstsearch(whitelist, pos + sf::Vector2i(0, -1), label, regionType);

    return;
}

void Map::findConnectedRegions(std::vector<TileType> whitelist, int regionType = 0) {
    int regions = 1;

    for (auto &tile : this->tiles) tile.regions[regionType] = 0;

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            bool found = false;
            for (auto type : whitelist) {
                if (type == this->tiles[y * this->width + x].tileType) {
                    found = true;
                    break;
                }
            }
            if (this->tiles[y * this->width + x].regions[regionType] == 0 && found) {
                depthfirstsearch(whitelist, sf::Vector2i(x, y), regions++, regionType);
            }
        }
    }
    this->numRegions[regionType] = regions;
}
