#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "texture_manager.hpp"

class GameState;

class Game {
public:

    Game();
    ~Game();

    const static int tileSize = 8;

    std::stack<GameState *> states;

    sf::RenderWindow window;
    TextureManager texmgr;
    sf::Sprite background;

    std::map<std::string, Tile> tileAtlas;

    void pushState(GameState *state);

    void popState();

    void changeState(GameState *state);

    GameState *peekState();

    void run();
private:

    void loadTextures();
    void loadTiles();
};

#endif /* GAME_HPP */
