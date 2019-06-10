#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class GameStateStart : public GameState {
public:

    virtual void draw(const float dt);

    virtual void update(const float dt);

    virtual void handleInput();

    GameStateStart(Game *game);

private:

    void loadgame();

    sf::View view;
};

#endif /* GAME_STATE_START_HPP */
