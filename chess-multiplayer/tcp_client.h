#include <iostream>	//cout
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <string>	//string
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <netdb.h>	//hostent
#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

using namespace std;

class tcp_client
{
private:
	int sock;
	string address;
	int port;
	struct sockaddr_in server;
	
public:
	tcp_client();
	bool conn(string, int);
	bool send_data(string data);
	string receive();
};

#endif