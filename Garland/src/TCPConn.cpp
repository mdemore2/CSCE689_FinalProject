#include "TCPConn.hpp"
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <iostream>

bool TCPConn::accept_conn(int socket) {

   struct sockaddr_in client_addr;
   socklen_t addrsize = sizeof(client_addr);
   this->sock = accept(socket, (struct sockaddr *) &client_addr, &addrsize );
   if(this->sock < 0)
      return false;

   return true;
}

int TCPConn::getSocket() {
   return this->sock;
}

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