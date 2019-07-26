#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "audiomanager.hpp"
#include "game.hpp"
#include "game_state.hpp"
#include "texture_manager.hpp"
#include "animation_handler.hpp"
#include "tile.hpp"

Game::Game()
{
    audio = std::make_unique<AudioManager>();
    textures = std::make_unique<TextureManager>();

    audio->load();
    audio->play("background", true);

    textures->load();

    loadTiles();

    window.create(sf::VideoMode(800, 600), "Mock City");
    window.setFramerateLimit(60);
    background.setTexture(textures->getRef("background"));
}

Game::~Game()
{
    while (!states.empty()) {
        popState();
    }
}

void Game::loadTiles()
{
    Animation staticAnim(0, 0, 1.0f);
    tileAtlas["grass"] =
            Tile(tileSize, 1, textures->getRef("grass"),
                 { staticAnim },
                 TileType::GRASS, 50, 0, 1);
    tileAtlas["forest"] =
            Tile(tileSize, 1, textures->getRef("forest"),
                 { staticAnim },
                 TileType::FOREST, 100, 0, 1);
    tileAtlas["water"] =
            Tile(tileSize, 1, textures->getRef("water"),
                 { Animation(0, 3, 0.5f),
                   Animation(0, 3, 0.5f),
                   Animation(0, 3, 0.5f) },
                 TileType::WATER, 0, 0, 1);
    tileAtlas["residential"] =
            Tile(tileSize, 2, textures->getRef("residential"),
                 { staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim, staticAnim },
                 TileType::RESIDENTIAL, 300, 50, 6);
    tileAtlas["commercial"] =
            Tile(tileSize, 2, textures->getRef("commercial"),
                 { staticAnim, staticAnim, staticAnim, staticAnim},
                 TileType::COMMERCIAL, 300, 50, 4);
    tileAtlas["industrial"] =
            Tile(tileSize, 2, textures->getRef("industrial"),
                 { staticAnim, staticAnim, staticAnim,
                   staticAnim },
                 TileType::INDUSTRIAL, 300, 50, 4);
    tileAtlas["road"] =
            Tile(tileSize, 1, textures->getRef("road"),
                 { staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim, staticAnim,
                   staticAnim, staticAnim },
                 TileType::ROAD, 100, 0, 1);
}

void Game::pushState(GameState *state)
{
    states.push(state);
}

void Game::popState()
{
    delete states.top();
    states.pop();
}

void Game::changeState(GameState *state)
{
    if (!states.empty()) {
        popState();
    }

    pushState(state);
}

GameState *Game::peekState()
{
    if (states.empty()) {
        return nullptr;
    }

    return states.top();
}

void Game::run()
{
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (peekState() == nullptr) {
            continue;
        }

        peekState()->handleInput();
        peekState()->update(dt);
        window.clear(sf::Color::Black);
        peekState()->draw(dt);
        window.display();

        audio->releaseFinished();
    }
}
