#include "primesvr.hpp"
#include "TCPConn.h"
#include <sys/socket.h>


PrimeServer::Primeserver(std::string ip_addr, unsigned int port) : ip_addr(ip_addr), port(port) {
}

bool PrimeServer::isPrime(uint8_t num) {
    // Mark, add your code here
}


void PrimeServer::start() {
    if((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        // Unrecoverable: if we cannot obtain a socket, we cannot have a server.
        throw std::runtime_error("Failed to create socket");

    // Set listener to Non-Blocking
    fcntl(this->sock, F_SETFL, O_NONBLOCK);

    if(setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
        throw std::runtime_error("Failed to set socket options");

    // Fill in address details such as port and IP for binding
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_addr);
    address.sin_port = htons( port );

    // Bind listener to port
    if(bind(this->sock, (struct  sockaddr *)&address, sizeof(address)) < 0)
        throw std::runtime_error("Binding error");

    // Start listening on main socket
    if(listen(this->sock, 2) < 0) {
        throw std::runtime_error("Hung Up on Listening");
    }


    // Two sets are needed, one for all sockets and another that will be modified by the read each time
    // fd_set all_sock, read_sock;
    fd_set all_sock, read_sock ;
    // // Max sock will keep track of the socket range we need to be checking
    int max_sock, new_sock;
    // // This keep tracks of the sockets and their TCPConn objects
    std::map<int, TCPConn*> connections;

    // Add this listener socket to our master list
    FD_SET(listener_sock, &all_sock);
    // Set as max socket until we find another
    max_sock = listener_sock;

    while(!prime) {


    }
}