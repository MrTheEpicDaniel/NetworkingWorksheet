#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window, bool server) :
  window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game() {}

bool Game::init()
{
  if (isServer)
  {
    std::cout << "creating server" << std::endl;
    server = std::make_unique<Server>();
    server->init();
    server->run();
  }
  else
  {
    std::cout << "creating client" << std::endl;
    client = std::make_unique<Client>();
    client->connect();
    client->run();
  }
  return true;
}

void Game::update(float dt) {}

void Game::render()
{
  // rendering goes here
}

void Game::mouseClicked(sf::Event event)
{
  // get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event) {}
