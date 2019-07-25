#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "game_state_editor.hpp"

GameStateEditor::GameStateEditor(Game *game) {
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(game->window.getSize());
    guiView.setSize(pos);
    gameView.setSize(pos);
    pos *= 0.5f;
    guiView.setCenter(pos);
    gameView.setCenter(pos);

    map = Map("city_map.dat", 64, 64, game->tileAtlas);

    this->zoomLevel = 1.0f;

    sf::Vector2f centre(this->map.width, this->map.height*0.5);
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);

    this->actionState = ActionState::NONE;
}

void GameStateEditor::draw(const float dt) {
    this->game->window.clear(sf::Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);

    this->game->window.setView(this->gameView);
    map.draw(this->game->window, dt);
}

void GameStateEditor::update(const float dt) {
}

void GameStateEditor::handleInput() {
    sf::Event event;

    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                game->window.close();
                break;
            }

            case sf::Event::Resized: {
                gameView.setSize(event.size.width, event.size.height);
                gameView.zoom(zoomLevel);
                guiView.setSize(event.size.width, event.size.height);
                game->background.setPosition(game->window.mapPixelToCoords(sf::Vector2i(0, 0), guiView));
                game->background.setScale(
                    float(event.size.width) / float(game->background.getTexture()->getSize().x),
                    float(event.size.height) / float(game->background.getTexture()->getSize().y)
                );
                break;
            }

            case sf::Event::MouseMoved: {
                if(this->actionState == ActionState::PANNING) {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
                    gameView.move(-1.0f * pos * this->zoomLevel);
                    panningAnchor = sf::Mouse::getPosition(this->game->window);
                }
                break;
            }

            case sf::Event::MouseButtonPressed: {
                if(event.mouseButton.button == sf::Mouse::Middle) {
                    if(this->actionState != ActionState::PANNING) {
                        this->actionState = ActionState::PANNING;
                        this->panningAnchor = sf::Mouse::getPosition(this->game->window);
                    }
                }
                break;
            }

            case sf::Event::MouseButtonReleased: {
                if(event.mouseButton.button == sf::Mouse::Middle) {
                    this->actionState = ActionState::NONE;
                }
                break;
            }

            case sf::Event::MouseWheelMoved: {
                if(event.mouseWheel.delta < 0) {
                    gameView.zoom(2.0f);
                    zoomLevel *= 2.0f;
                } else {
                    gameView.zoom(0.5f);
                    zoomLevel *= 0.5f;
                }
                break;
            }

            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
                break;
            }

            default:
                break;
        }
    }
}
