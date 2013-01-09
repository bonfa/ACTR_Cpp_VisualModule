/*
 * Server.cpp
 *
 *  Created on: 05/dic/2012
 *      Author: enrico
 */
 


//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

//g++ -I/usr/include/jsoncpp Server.cpp -o EchoServer -lboost_system -lboost_system-mt -pthread -ljsoncpp
//richiede libbost-all-dev


#include "Server.h"

/*
//extern "C" int *init (int i);
using boost::asio::ip::tcp;

std::string message = "Waiting to receive data\nIn telnet type: '{\"data\": \"Contenuto\"}' and hit return, close telnet to terminate\n";



class server
{
public:
  server(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
  {
    start_accept();
  }


private:
  void start_accept()
  {
    session* new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(session* new_session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
      new_session->start();
    }
    else
    {
      delete new_session;
    }

    start_accept();
  }

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};

*/
/*
int runServer(int port)
{
  try
  {
    if (port<0)
    {
      std::cerr << "Porta del server negativa\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server s(io_service, port);

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

int main(){
	runServer(4114);
	}
*/
