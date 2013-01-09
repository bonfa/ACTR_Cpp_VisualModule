#include "Session.h"

/*
tcp::socket& socket()
  {
    return socket_;
  }

  void start()
  {
	 
std::string message = "Waiting to receive data\nIn telnet type: '{\"data\": \"Contenuto\"}' and hit return, close telnet to terminate\n";

	   boost::asio::write(socket_, boost::asio::buffer(message));
	   
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&session::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
		std::string output = decodeJson(data_);
		
		//std::string s = "Hello, world";
		//std::vector<char> v(s.begin(), s.end());
		//v.push_back('\0'); // Make sure we are null-terminated
		//char* c = &v[0];
		
		//str.assign(data_, 6);
		
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
}*/