#ifndef SESSION_H_
#define SESSION_H_

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <json/json.h>

using boost::asio::ip::tcp;

std::string messaggio = "Waiting to receive data\nIn telnet type: '{\"data\": \"Contenuto\"}' and hit return, close telnet to terminate\n";

class Session
{
public:
  Session(boost::asio::io_service& io_service)
    : socket_(io_service)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
	 

	   boost::asio::write(socket_, boost::asio::buffer(messaggio));
	   
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&Session::handle_read, this,
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
          boost::bind(&Session::handle_write, this,
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
          boost::bind(&Session::handle_read, this,
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

#endif /* SESSION_H_ */
