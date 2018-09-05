#ifndef TCP_SERVER_H
#define TCP_SERVER_H 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <string.h>

using namespace std;

class tcp_server
{
private:
    int sockfd, newsockfd, portno;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    void error(const char *msg);
public:
    tcp_server();

    bool create_socket(int _portno);

    bool accept_tcp();
    string listen_tcp();
    bool write_tcp(string s);

    void close_tcp();
    ~tcp_server();

    /* data */
};

#endif