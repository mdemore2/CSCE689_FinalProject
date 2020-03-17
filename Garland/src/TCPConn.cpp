#include "TCPConn.hpp"
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <iostream>

/********************************************************************************************
*   accept_conn():  Accepts an incoming connection                                          *
*                                                                                           *
*   Parameters:     the listening socket                                                    *
*                                                                                           *
*   Return:         true if good accept, false otherwise                                    *
*********************************************************************************************/
bool TCPConn::accept_conn(int socket) {

   struct sockaddr_in client_addr;
   socklen_t addrsize = sizeof(client_addr);
   this->sock = accept(socket, (struct sockaddr *) &client_addr, &addrsize );
   if(this->sock < 0)
      return false;

   return true;
}

/*********************************************************************************************
*   getSocket():  returns this object's socket                                               *
*                                                                                            *
*   Parameters:   n/a                                                                        *
*                                                                                            *
*   Return:       the socket                                                                 *
**********************************************************************************************/
int TCPConn::getSocket() {
   return this->sock;
}

/********************************************************************************************
*   handleConnection():  handles a new connection                                           *
*                                                                                           *
*   Parameters:     n/a                                                                     *
*                                                                                           *
*   Return:         true if good msg, false otherwise                                       *
*********************************************************************************************/
bool TCPConn::handleConnection() {
   char msg[8];
   int msg_len = recv(sock, msg, 8, 0);

   if(msg_len == 0) {
      return false;
   }

   msg[msg_len] = '\0';
   std::string msg_str(msg);

   if(msg_str == "true") {
      std::cout << "Another server found an answer!\n";
      return true;
   } else {
      std::cout << "Received " << msg << "\n";
      return false;
   }
   

}