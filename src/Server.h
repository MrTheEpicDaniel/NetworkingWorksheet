#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <thread>

class Server
{
 public:
  void init();
  void run();
  void listen(sf::TcpSocket& cSocket);
  void send(std::string buffer);

 private:
  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;

  std::unique_ptr<sf::TcpListener> listener; //defines a unique pointer that will point to a TcpListener
  std::unique_ptr<sf::TcpSocket> socket;

  bool running = true;
  std::mutex mutex;

  


};
