#pragma once

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>
#include <thread>

class Client
{
 public:
  void connect();
  void input(sf::TcpSocket& iSocket) const;
  void run();

  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;

  private:
  std::unique_ptr<sf::TcpSocket> socket;
};
