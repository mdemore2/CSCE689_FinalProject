#ifndef TCPCONN_H
#define TCPCONN_H

class TCPConn
{
   public:

   bool accept_conn(int socket);
   bool handleConnection();

   int getSocket();

   private:
   int sock;
};


#endif