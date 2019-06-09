#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>
#include "texture_manager.hpp"

class GameState;

class Game {
public:

    Game();
    ~Game();

    std::stack<GameState *> states;

    sf::RenderWindow window;
    TextureManager texmgr;
    sf::Sprite background;

    void pushState(GameState *state);

    void popState();

    void changeState(GameState *state);

    GameState *peekState();

    void run();
private:

    void loadTextures();
};

#endif /* GAME_HPP */
