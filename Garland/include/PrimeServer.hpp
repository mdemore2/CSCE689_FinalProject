#ifndef PRIMESERVER_H
#define PRIMESERVER_H

#include "Server.h"
#include <stdint.h>
#include <string>

class PrimeServer
{
    public:
    PrimeServer(std::string ip_addr, unsigned int port);
    ~PrimeServer();

    bool isPrime(uint8_t num);
    void start();

    private:

    std::string ip_addr;
    unsigned int port;
    unsigned int sock = -1;
    bool prime = false;
    
};

#endif