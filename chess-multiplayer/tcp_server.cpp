/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "tcp_server.h"

tcp_server::tcp_server() 
{

}

void tcp_server::error(const char *msg)
{
    perror(msg);
}

bool tcp_server::create_socket(int _portno)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        error("ERROR opening socket");
        return false;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = _portno;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
        return false;
    }
    return true;
}

bool tcp_server::accept_tcp()
{
    socklen_t clilen;
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,  (struct sockaddr *) &cli_addr,  &clilen);
    if (newsockfd < 0) {
        error("ERROR on accept");
        return false;
    }
    return true;
}
string tcp_server::listen_tcp()
{
    char buffer[256];
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    return buffer;
}
bool tcp_server::write_tcp(string data)
{
    
    n = write(newsockfd,data.c_str() , strlen( data.c_str() ));
    if (n < 0)
    {
        error("ERROR writing to socket");
        return false;
    }
    return true;
}

void tcp_server::close_tcp()
{
    close(newsockfd);
    close(sockfd);
}
tcp_server::~tcp_server()
{

}