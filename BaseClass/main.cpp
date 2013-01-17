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
# define IMG_PATH_01 "./images/01_02_1030797656577.bmp"
# define IMG_PATH_02 "./images/02_08_447099175936.bmp"
# define IMG_PATH_03 "./images/03_32_9007255098753112.bmp"
# define IMG_PATH_04 "./images/04_36_1478332047688192.bmp"
# define IMG_PATH_05 "./images/05_50_1548318539776144.bmp"
# define IMG_PATH_06 "./images/06_54_18023194906722704.bmp"
# define IMG_PATH_07 "./images/07_04_219903404277765.bmp"
# define IMG_PATH_08 "./images/08_06_114392163942656.bmp"
# define IMG_PATH_09 "./images/09_25_1337006283030553.bmp"
# define IMG_PATH_10 "./images/10_26_1548114663047204.bmp"
# define IMG_PATH_11 "./images/11_29_11261199174860888.bmp"
# define IMG_PATH_12 "./images/12_53_145525316052451328.bmp"		//TODO quadrato esterno
# define IMG_PATH_13 "./images/13_59_142118473433600.bmp"		//TODO	quadrato esterno
# define IMG_PATH_14 "./images/14_NA_498222760961.bmp"
# define IMG_PATH_15 "./images/15_NA_10793261728000.bmp"
# define IMG_PATH_16 "./images/16_NA_211142744211593.bmp"
# define IMG_PATH_17 "./images/17_NA_72480910316142593.bmp"		//TODO  quadrato esterno
# define IMG_PATH_18 "./images/18_NA_577445915800635392.bmp"
# define IMG_PATH_19 "./images/19_NA_580260668791324672.bmp"		//TODO	quadrato esterno
# define IMG_PATH_20 "./images/20_NA_583224952673546240.bmp"
# define IMG_PATH_21 "./images/21_NA_584350852048749056.bmp"
# define IMG_PATH_22 "./images/22_NA_865966563026534912.bmp"
# define IMG_PATH_23 "./images/23_NA_867083665762158848.bmp"
# define IMG_PATH_24 "./images/24_M01_216770917518016516.bmp"



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
	printChunkList(chunkList);
	#endif
	
    
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

	
}


