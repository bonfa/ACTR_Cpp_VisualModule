/*
 * main.cpp
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 */

#include "src/proxy.h"
#include "src/Server.h"
#include "src/utils.h"
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>  

//int runServer(int port);


int main(){
	std::cout << "a\n";
	try
  {
     boost::asio::io_service io_service;
    Server s(io_service, 4114);

	//boost::asio::io_service::work work(io_service);
    
    boost::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
    
    //io_service.run();
    

	Proxy *p = new Proxy();
	p->demo();
	
    std::cout << "Press enter to terminate whenever you want!" << std::endl;
	std::string request;
	std::getline(std::cin, request);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

	
}


