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

//g++ -I/usr/include/jsoncpp echoServer.cpp -o EchoServer -lboost_system -lboost_system-mt -pthread -ljsoncpp
//richiede libbost-all-dev

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <json/json.h>
#include "Server.h"

//extern "C" int *init (int i);
using boost::asio::ip::tcp;

std::string message = "Waiting to receive data\nIn telnet type: '{\"data\": \"Contenuto\"}' and hit return, close telnet to terminate\n";

class session
{
public:
  session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
	 

	   boost::asio::write(socket_, boost::asio::buffer(message));
	   
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
		std::string output = decodeJson(data_);
		/*
		std::string s = "Hello, world";
		std::vector<char> v(s.begin(), s.end());
		v.push_back('\0'); // Make sure we are null-terminated
		char* c = &v[0];
		
		str.assign(data_, 6);*/
		
      boost::asio::async_write(socket_,
          boost::asio::buffer(output.c_str(),output.length()),
          boost::bind(&session::handle_write, this,
            boost::asio::placeholders::error));
    }
    else
    {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
		
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
  }
  
  static std::string decodeJson(std::string json){
	std::stringstream stream;


	Json::Value root;
	Json::Reader reader;
	bool parsedSuccess = reader.parse(json, root, false);

	if(not parsedSuccess)
	{
		// Report failures and their locations
		// in the document.
		stream<<"Failed to parse JSON"<<std::endl <<reader.getFormatedErrorMessages() <<std::endl;
	}

	//suppongo che ci sia un campo chiamato "data" ed estraggo il relativo valore
	const Json::Value notAnArray = root["data"];

	if(not notAnArray.isNull())
	{
		stream<< notAnArray.asString() <<std::endl;
	}

	//stream<<"Json Example pretty print: " <<std::endl<<root.toStyledString() <<std::endl;

	return stream.str();
}

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

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
