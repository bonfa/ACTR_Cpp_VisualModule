#ifndef SESSION_H_
#define SESSION_H_



#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string/join.hpp>

#include <json/json.h>

#include "PathConstants.h"
#include "proxy.h"


using boost::asio::ip::tcp;




class Session
{
public:
		Session(boost::asio::io_service& io_service)
: socket_(io_service)
{
		proxyMarker = new Proxy();
}

	tcp::socket& socket();

	void start();

private:
	void setChunk(Proxy *p);

	void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred);

	void handle_write(const boost::system::error_code& error);

	static std::string decodeJson(std::string json);

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
	vector<string> chunks;
	Proxy *proxyFeature;
	Proxy *proxyMarker;

};



#endif /* SESSION_H_ */
