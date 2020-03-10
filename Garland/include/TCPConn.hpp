#ifndef TCPCONN_H
#define TCPCONN_H

class TCPConn
{
   public:

   bool accept(int socket);
   bool handleConnection();

   int getSocket();

   private:
   int socket;
};


#endif