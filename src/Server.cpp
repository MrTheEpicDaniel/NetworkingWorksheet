#include "Server.h"

void Server::init()
{
  if (listener == nullptr)
  {
    listener = std::make_unique<sf::TcpListener>(); // gives the listener
                                                    // pointer a listener to
                                                    // point to
  }
  // bind listener to a port
  if (listener->listen(53000) != sf::Socket::Done)
  {
    // error...
    std::cout << "listener failed to listen to port 53000" << std::endl;
  }
}
void Server::run()
{
  while (running)
  {
    // add pointer for new_connection and get reference to it
    // when we get a new connection(Socket)
    // if the new_connection is invalid - return
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>())
        .
        operator*(); // emplace a unique pointer for TcpSocket at the back of
                     // connections, then dereference it using "operator*()" and
                     // set a reference called cSock equal to that dereferenced
                     // unique pointer
    if (listener->accept(cSock) != sf::Socket::Done)
    {
      connections.pop_back(); // removes invalid connection
      return;
    }
    std::cout << "Client connected @ " << cSock.getRemotePort() << std::endl;

    workers.emplace_back(
      [&]
      {
        listen(cSock);
        std::cout << "detected disconnect\n";
        std::lock_guard<std::mutex> lck(mutex);

        for (int i = 0; i < connections.size(); ++i)
        {
          if (connections[i]->getLocalPort() == cSock.getLocalPort())
            continue;
          connections.erase(std::next(connections.begin(), i));
          break;
        }
      });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

// add new_connection to connections
// set up the connection for listening & sending
void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;

  char data[1028];
  std::size_t received;

  while (continue_receiving)
  {
    auto status = cSocket.receive(data, 1028, received);

    if (status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false;
      std::cout << "Disconnected" << std::endl;
    }
    if (received < 1028)
    {
      data[received] = '\0';
    }
    send(data);
    std::cout << reinterpret_cast<char*>(data) << '\n';
  }
  cSocket.disconnect();
}

void Server::send(std::string buffer)
{
  auto message = reinterpret_cast<char*>(buffer.data());

  std::lock_guard<std::mutex> lck(mutex);

  for (auto& connection : connections)
  {
    connection->send(message, buffer.size());
  }
}