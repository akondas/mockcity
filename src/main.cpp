#include "game.hpp"
#include "game_state_start.hpp"
#include "logger.hpp"

int main() {
    g_logger->setLogFilePath("log.txt");

    Game game;
    game.pushState(new GameStateStart(&game));
    game.run();

    return 0;
}
