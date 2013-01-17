/*
 * main.cpp
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 */

#include "src/proxy.h"
#include "src/Server.h"

#include "src/MarkerDetector.h"
#include <boost/thread/mutex.hpp>

#include "src/utils.h"
#include "src/author.h"
#include <iostream>

//#ifdef ENRICO
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>  
//#endif

//int runServer(int port);

//# define IMG_PATH_01 "./shapes.png";
//# define IMG_PATH_02 "./ellipses.jpg";

#include "src/PathConstants.h"



#ifdef ENRICO
 //Run Enrico's code
//ottimo esempio sui mutex
//http://www.drdobbs.com/cpp/the-boostthreads-library/184401518?pgno=2
//public static boost::mutex io_mutex;
#endif

void printChunkList(vector<string> chunkList){
	for (unsigned int i=0; i<chunkList.size();i++)
			cout << chunkList.at(i) << endl;
}
	
int main(){
	try
  {


	  //Run Enrico's code
	 //std::cout << stub();
	 std::cout << "Running Enrico's stuff \n";
	 
     boost::asio::io_service io_service;
     //Create server listening on port 4114, and put it in the list of services to be run
    Server s(io_service, 4114);
	//boost::asio::io_service::work work(io_service);
    
    //Create a new boost thread and run all the io_service services
    boost::thread bt(boost::bind(&boost::asio::io_service::run, &io_service));
 	std::cout << "Server running in background \n";
   
    //io_service.run();
 	Proxy *p = new Proxy();
 	p->demoEnrico();

	 #ifdef ENRICO

    //Prevent program from terminating, needed for server to stay alive
	startDetection();	
	
	std::string str;
	std::cout<<"Ctrl + c to terminate!\n";
	std::cin >>str;



	#else 	  //Run Francesco's code
	std::cout << "Running Francesco's stuff \n";
	Proxy *p2 = new Proxy(IMG_PATH_12);
	vector<string> chunkList = p2->getChunkList();
	//printChunkList(chunkList);
	std::string str;
	std::cout<<"Ctrl + c to terminate!\n";
	std::cin >>str;
	#endif
	
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

	
}


