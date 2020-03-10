#include "primesvr.hpp"
#include "TCPConn.h"
#include <sys/socket.h>

Primesvr::Primesvr(std::string ip_addr, unsigned int port) : ip_addr(ip_addr), port(port) {
}

bool Primeserver::isPrime(uint8_t num) {
    // Mark, add your code here
}


void Primeserver::start() {
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        // Unrecoverable: if we cannot obtain a socket, we cannot have a server.
        throw std::runtime_error("Failed to create socket");

    // Set listener to Non-Blocking
    fcntl(sock, F_SETFL, O_NONBLOCK);

    if(setsockopt(socke, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
        throw std::runtime_error("Failed to set socket options");

    // Fill in address details such as port and IP for binding
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_addr);
    address.sin_port = htons( port );

    // Bind listener to port
    if(bind(sock, (struct  sockaddr *)&address, sizeof(address)) < 0)
        // Unrecoverable: if our listener socket does not bind, we do not have a server.
        throw std::runtime_error("Binding error");

    // Two sets are needed, one for all sockets and another that will be modified by the read each time
    fd_set all_sock, read_sock;
    // Max sock will keep track of the socket range we need to be checking
    int max_sock, new_sock;
    // This keep tracks of the sockets and their TCPConn objects
    std::map<int, TCPConn> connections;

    // Start listening on one socket
    if(listen(sock, 2) < 0)
        // Unrecoverable: a server must be able to listen
        throw std::runtime_error("Hung Up on Listening");

    // std::cout << "Started Listening..\n";

    // Add this listener socket to our master list
    FD_SET(sock, &all_sock);
    // Set as max socket until we find another
    max_sock = sock;

    while(true)
    {
        // Read sock is modified by select so we must reset it each time
        read_sock = all_sock;
        // std::cout << "\nServer: Looping\n";

        if(select(max_sock+1, &read_sock, NULL, NULL, NULL) < 0)
        {
            // Unrecoverable: if we cannot find the socket, we wont be able
            // to process any data
            throw socket_error("Select error");
        }
        std::cout << "New Data!\n";
        // Loop through all of our sockets and check which ones have data
        for(int i=0; i <= max_sock; i++)
        {
            // If this socket is in the set of sockets that has data
            if(FD_ISSET(i, &read_sock))
            {
                // New connection because the listener socket has data
                if(i == listener_sock)
                {
                    std::cout << "New Connection!\n";
                    TCPConn new_conn();
                    if(new_conn->accept_conn(listener_sock) == false)
                    {
                        // Recoverable: Sometimes it may not accept a connection
                        throw socket_error("Error: Accepting new Connection");
                    }

                    new_sock = new_conn->getSocket();

                    if(new_sock > max_sock) {max_sock = new_sock;}
                    // Add the new socket to our master list
                    FD_SET(new_sock, &all_sock);
                    connections.insert({new_sock, new_conn});
                }
                // Data from an existing connection
                else
                {
                    std::cout << "Existing Connection\n";
                    // Loop through our map of sockets and tcpconn objects
                    for(auto const& [key, val] : connections)
                    {
                        if(key == i)
                        {
                            // If the connection is closed, clear it from our list
                            if(!val->handleConnection())
                            {
                                FD_CLR(key, &all_sock);
                            }
                        }
                    }
                }
            }
        }

    }


    

    

}