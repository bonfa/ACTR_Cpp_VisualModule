/*
 * main.cpp
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 */

#include "src/proxy.h"
#include "src/Server.h"

#include "src/MarkerDetector.h"


#include "src/utils.h"
#include "src/author.h"
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>  

//int runServer(int port);


int main(){
	std::cout << "a\n";
	try
  {
	  
	 #ifdef ENRICO //Run Enrico's code
	 std::cout << stub();
	 std::cout << "Running Enrico's stuff \n";
     boost::asio::io_service io_service;
     //Create server listening on port 4114, and put it in the list of services to be run
    Server s(io_service, 4114);
	std::cout << "b\n";
	//boost::asio::io_service::work work(io_service);
    
    //Create a new boost thread and run all the io_service services
    boost::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
    
    //io_service.run();
    std::cout << "c\n";
    
    //Prevent program from terminating, needed for server to stay alive
	std::string str;
	std::cout<<"Press enter to terminate whenever you want!\n";
	std::cin >>str;

	#else 	  //Run Francesco's code
	std::cout << "Running Francesco's stuff \n";
	Proxy *p = new Proxy();
	p->demo();
	
	#endif
	
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

	
}


