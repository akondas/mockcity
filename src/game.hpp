#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>

#include "audiomanager.hpp"
#include "texture_manager.hpp"
#include "tile.hpp"

constexpr uint16_t tileSize = 8;

class GameState;

class Game
{
    public:

        Game();
        ~Game();

        std::stack<GameState *> states;

        sf::RenderWindow window;
        sf::Sprite background;

        std::map<std::string, Tile> tileAtlas;

        void pushState(GameState *state);

        void popState();

        void changeState(GameState *state);

        GameState *peekState();

        void run();

        void loadTiles();

    private:
        std::unique_ptr<AudioManager> audio{nullptr};
        std::unique_ptr<TextureManager> textures{nullptr};
};

#endif /* GAME_HPP */
