/*
 * Server.h
 *
 *  Created on: 05/dic/2012
 *      Author: enrico
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <json/json.h>
#include "Session.h"
#include "FeatureExtractor.h"
#include "PathConstants.h"
#include "proxy.h"


using boost::asio::ip::tcp;

class Server
{
public:
	Server(boost::asio::io_service& io_service, short port)
: io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
{
		start_accept();
}


private:
	void start_accept();

	void handle_accept(Session* new_session,const boost::system::error_code& error);

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};

#endif /* SERVER_H_ */
