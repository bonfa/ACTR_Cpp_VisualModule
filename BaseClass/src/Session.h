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
#include "author.h"


using boost::asio::ip::tcp;




class Session
{
public:
//<<<<<<< HEAD
	Session(boost::asio::io_service& io_service)
: socket_(io_service)
{
#ifdef ENRICO
		proxyMarker = new Proxy();
#endif
}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{

		std::string messag = "Waiting to receive data\nIn telnet type: '{\"cmd\":\"getMarker\"}' and hit return, close telnet to terminate\n";

		boost::asio::write(socket_, boost::asio::buffer(messag));

		socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&Session::handle_read, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}
/*
	=======
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
	 
	  	  std::string messag = "Waiting to receive data\nIn telnet type: '{\"data\": \"Contenuto\"}' and hit return, close telnet to terminate\n";


	   boost::asio::write(socket_, boost::asio::buffer(messag));

	   IMG_PATH_12
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&Session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
>>>>>>> a17883ca40c3f829f39d833d82da8f1f26c5e561
 */
private:
	void setChunk(Proxy *p){

		chunks = p->getChunkList();
		//vector<string> chunkList;
	}

	void handle_read(const boost::system::error_code& error,
			size_t bytes_transferred)
	{
		if (!error)
		{
			std::string command = decodeJson(data_);


			std::cout << "comando ricevuto :" << command << "\n";

			std::string finalString = "";

			//If the command is getChunks
			if(command.compare("getFeature") == 0){
				proxyFeature = new Proxy(IMG_PATH_12);
				setChunk(proxyFeature);
				finalString = "[";
				std::string joinedString = boost::algorithm::join(chunks, ",");
				finalString.append(joinedString);
				finalString.append("]");
			}
#ifdef ENRICO
			else if(command.compare("getMarker") == 0){
				chunks = proxyMarker->getMarkerList();
				//setChunk(proxyMarker);
				finalString = "[";
				std::string joinedString = boost::algorithm::join(chunks, ",");
				finalString.append(joinedString);
				finalString.append("]");
			}
#endif
			boost::asio::async_write(socket_,
					boost::asio::buffer(finalString.c_str(),finalString.length()),
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
		const Json::Value notAnArray = root["cmd"];

		if(not notAnArray.isNull())
		{
			stream<< notAnArray.asString();
		}

		if(stream.str().compare("get\n") == 0)
			cout << "barra enne \n";

		//stream<<"Json Example pretty print: " <<std::endl<<root.toStyledString() <<std::endl;
		cout << stream.str();

		return stream.str();
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
	vector<string> chunks;
	Proxy *proxyFeature;
#ifdef ENRICO
	Proxy *proxyMarker;
#endif
};



#endif /* SESSION_H_ */
