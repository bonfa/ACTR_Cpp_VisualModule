/*
 * Server.cpp
 *
 *  Created on: 05/dic/2012
 *      Author: enrico
 */
#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <json/json.h>
#include <sstream>


int respond(int new_sd);
extern "C" int *init (int i);

/*
struct c_struct
     {
       int x;
       char *s;
     };*/

int *init (int i)
{



    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.

    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in c++, it will be given a block of memory. This memory is not nessesary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof host_info);

    std::cout << "Setting up the structs..."  << std::endl;

    host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
    host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

    status = getaddrinfo(NULL, "5556", &host_info, &host_info_list);
    // getaddrinfo returns 0 on succes, or some other value when an error occured.
    // (translated into human readable text by the gai_gai_strerror function).
    if (status != 0)  std::cout << "getaddrinfo error" << gai_strerror(status) ;


    std::cout << "Creating a socket..."  << std::endl;
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                      host_info_list->ai_protocol);
    if (socketfd == -1)  std::cout << "socket error " ;

    std::cout << "Binding socket..."  << std::endl;
    // we use to make the setsockopt() function to make sure the port is not in use
    // by a previous execution of our code. (see man page for more information)
    int yes = 1;
    status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  std::cout << "bind error" << std::endl ;

    std::cout << "Listen()ing for connections..."  << std::endl;
	std::cout << "Example of usage: $telnet 127.0.0.1 5556\n";
    status =  listen(socketfd, 5);
    if (status == -1)  std::cout << "listen error" << std::endl ;


    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_sd == -1)
    {
        std::cout << "listen error" << std::endl ;
    }
    else
    {
        std::cout << "Connection accepted. Using new socketfd : "  <<
new_sd << std::endl;
    }

    while(true){
    	int status = respond( new_sd);
    	if (status == 0) {
    		std::cout << "Session terminated\n";
    		break;
    	}
    	else if (status == -1) {
    	    		std::cout << "Receive error\n";
    	    		break;
    	    	}
    }
    freeaddrinfo(host_info_list);
    close(new_sd);
    close(socketfd);

    //return 0 ;


    //struct c_struct *r2;
    //r2 = (struct c_struct *) malloc (sizeof(struct c_struct));
    //r2->x = i + 5;
    //r2->s = "a C string";
    return 0;


}

std::string decodeJson(std::string json){
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

	const Json::Value notAnArray = root["data"];

	if(not notAnArray.isNull())
	{
		stream<< notAnArray.asString() <<std::endl;
	}

	//stream<<"Json Example pretty print: " <<std::endl<<root.toStyledString() <<std::endl;

	return stream.str();
}

int respond(int new_sd){
	std::cout << "Waiting to recieve data..."  << std::endl;
	std::cout << "In telnet type: '{\"data\": \"Contenuto\"}' and hit return, close telnet to terminate\n";

			ssize_t bytes_recieved;
	char incomming_data_buffer[1000];
	bytes_recieved = recv(new_sd, incomming_data_buffer,1000, 0);

	// If no data arrives, the program will just wait here until some data arrives.
	if (bytes_recieved == 0) return 0;
	if (bytes_recieved == -1) return -1 ;

	incomming_data_buffer[bytes_recieved] = '\0';
	std::cout <<"Ricevuto:"<< incomming_data_buffer << std::endl;


	std::string decoded = decodeJson(incomming_data_buffer);


	std::cout << "Decodificato il JSON:" << decoded << std::endl ;



	std::cout << "send()ing back a message...";

	char *msg = "Respond";
	int len;
	ssize_t bytes_sent;
	len = strlen(msg);
	bytes_sent = send(new_sd, msg, len, 0);

	return bytes_recieved;
}



