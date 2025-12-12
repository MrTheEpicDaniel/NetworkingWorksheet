#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "Client.h"
#include "Server.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window, bool server);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  bool isServer = true;

  std::unique_ptr<Client> client = nullptr;
  std::unique_ptr<Server> server = nullptr;

  sf::RenderWindow& window;
};

#endif // PLATFORMER_GAME_H
