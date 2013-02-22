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

void Server::start_accept()
	{
		Session* new_session = new Session(io_service_);
		acceptor_.async_accept(new_session->socket(),
				boost::bind(&Server::handle_accept, this, new_session,
						boost::asio::placeholders::error));
	}
	
void Server::handle_accept(Session* new_session,
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

