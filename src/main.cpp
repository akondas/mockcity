#include "game.hpp"
#include "game_state_start.hpp"

int main() {
    Game game;
    game.pushState(new GameStateStart(&game));
    game.run();

    return 0;
}
