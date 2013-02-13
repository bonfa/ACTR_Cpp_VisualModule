#include "Session.h"

tcp::socket& Session::socket()
	{
		return socket_;
	}

void Session::start()
	{

		std::string messag = "Waiting to receive data\nIn telnet type: '{\"cmd\":\"getMarker\"}' and hit return, close telnet to terminate\n";

		//boost::asio::write(socket_, boost::asio::buffer(messag));

		socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&Session::handle_read, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}
	
void Session::setChunk(Proxy *p){

		chunks = p->getChunkList();
		//vector<string> chunkList;
	}

void Session::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
	{
		if (!error)
		{
			std::string command = decodeJson(data_);


			std::cout << "comando ricevuto :" << command << "\n";

			std::string finalString = "";

			//If the command is getChunks
			if(command.compare("getFeature") == 0){
				proxyFeature = new Proxy(IMG_PATH_01);
				setChunk(proxyFeature);
				finalString = "[";
				std::string joinedString = boost::algorithm::join(chunks, ",");
				finalString.append(joinedString);
				finalString.append("]\n");
				//cout << finalString;
			}
			else if(command.compare("getMarker") == 0){
				chunks = proxyMarker->getMarkerList();
				//setChunk(proxyMarker);
				finalString = "[";
				std::string joinedString = boost::algorithm::join(chunks, ",");
				finalString.append(joinedString);
				finalString.append("]\n");
			}

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

void Session::handle_write(const boost::system::error_code& error)
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

std::string Session::decodeJson(std::string json){

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