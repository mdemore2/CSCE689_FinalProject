#include "PrimeServer.hpp"
#include "TCPConn.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <memory>
#include <string.h>
#include <unistd.h>
#include <iostream>


PrimeServer::PrimeServer(std::string ip_addr, unsigned int port, unsigned int prime) : ip_addr(ip_addr), port(port), prime(prime) {
}

bool PrimeServer::checkPrime() {
    // Mark, add your code here
}

void PrimeServer::start() {
    if((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        // Unrecoverable: if we cannot obtain a socket, we cannot have a server.
        throw std::runtime_error("Failed to create socket");
    // Set listener to Non-Blocking
    fcntl(this->sock, F_SETFL, O_NONBLOCK);

    int opt = 1;
    if(setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
        throw std::runtime_error("Failed to set socket options");

    // Fill in address details such as port and IP for binding
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_addr.c_str());
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
    fd_set all_sock, read_sock;
    // Max sock will keep track of the socket range we need to be checking
    int max_sock, new_sock;
    // This keep tracks of the sockets and their TCPConn objects
    std::vector<TCPConn> connections;

    // Add listener socket to our master list
    FD_SET(this->sock, &all_sock);
    // Set as max socket until we find another
    max_sock = this->sock;
    if(port == 9997) {
        usleep(3000000);
        sendMsg();
    }
    while(!is_prime) {
        
        // Read sock is modified by select so we must reset it each time
        read_sock = all_sock;

        if(select(max_sock+1, &read_sock, NULL, NULL, NULL) < 0)
        {
            // Unrecoverable: if we cannot find the socket, we wont be able
            // to process any data
            throw std::runtime_error("Select error");
        }
        // Loop through all of our sockets and check which ones have data
        for(int i=0; i <= max_sock; i++)
        {
            // If this socket is in the set of sockets that has data
            if(FD_ISSET(i, &read_sock))
            {
                // New connection because the listener socket has data
                if(i == this->sock)
                {
                    std::cout << "New Connection!\n";
                    TCPConn new_conn;
                    if(new_conn.accept_conn(this->sock) == false)
                        std::cout << "\nError: Accepting new Connection\n";

                    new_sock = new_conn.getSocket();

                    if(new_sock > max_sock) 
                        max_sock = new_sock;
                    
                    // Add the new socket to our master list
                    FD_SET(new_sock, &all_sock);
                    connections.push_back(new_conn);
                }
                // Data from an existing connection
                else
                {
                    std::cout << "Existing Connection\n";
                    // Loop through our map of sockets and tcpconn objects
                    for(auto conn : connections)
                    {
                        if(i == conn.getSocket())
                        {
                            // If the connection is closed, clear it from our list
                            if(!conn.handleConnection())
                                FD_CLR(conn.getSocket(), &all_sock);
                        }
                    }
                }
            }
        }
    }
}

bool PrimeServer::sendMsg() {
    unsigned int port1, port2;
    if(port == 9997) {
        port1 = 9998;
        port2 = 9999;
    } else if (port == 9998)
    {
        port1 = 9997;
        port2 = 9999;
    } else
    {
        port1 = 9997;
        port2 = 9998;
    }
    int send_sock;
    if(( send_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        std::cout << "Failed to get sending socket\n";
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    address.sin_port = htons( port1 );
    std::cout << "Client: Connecting to server1...\n";
    int conn;
    if(connect(send_sock, (struct  sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Trouble connecting to port " << port1 << "\n";
    } else
    {
        std::string msg = "true";
        send(send_sock, msg.c_str(), strlen(msg.c_str()), 0);
    }
    close(send_sock);
    
    std::cout << "Connecting to server2\n";
    address.sin_port = htons( port2 );
    if(( send_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        std::cout << "Failed to get sending socket\n";
    if(connect(send_sock, (struct  sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cout << "Trouble connecting to port " << port2 << "\n";
    } else
    {
        std::string msg = "true";
        send(send_sock, msg.c_str(), strlen(msg.c_str()), 0);
    }
    close(send_sock);
    return true;
    
}