#include "Client.h"

void Client::connect()
{
    socket = std::make_unique<sf::TcpSocket>();
  std::cout << "connect called" << std::endl;
  if (socket->connect("127.0.0.1", 53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected!" << std::endl;
    connected = true;
  }
  else
  {
    std::cout << "failed to connect" << std::endl;
  }
}

void Client::run()
{
  running = true;

  std::thread input_thread([&] { input(*socket); });
  input_thread.detach();

  while (running && connected)
  {
    char static_buffer[1028];
    while (connected)
    {
      std::size_t received;
      auto status = socket->receive(static_buffer, 1028, received);

      if (status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket->disconnect();
        break;
      }
      else
      {
        if (received < 1028)
          static_buffer[received] = '\0';
        std::cout << static_buffer << '\n';
      }
    }
  }
}

void Client::input(sf::TcpSocket& iSocket) const
{
  while (running)
  {
    std::string str;

    std::getline(std::cin, str);
    std::cin.clear();

    if (connected)
    {
      iSocket.send(reinterpret_cast<char*>(str.data()), str.length());
    }
  }
}