#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game.hpp"

class GameState {
public:

    virtual ~GameState() = default;

    virtual void draw(const float dt) = 0;

    virtual void update(const float dt) = 0;

    virtual void handleInput() = 0;

    Game *game;
};

#endif /* GAME_STATE_HPP */
