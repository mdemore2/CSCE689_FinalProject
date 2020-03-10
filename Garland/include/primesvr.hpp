#ifndef PRIMESVR_H
#define PRIMESVR_H

#include "Server.h"
#include <stdint.h>
#include <string>

class Primesvr : public Server 
{
    public:
    Primesvr(std::string ip_addr, unsigned int port);
    ~Primesvr();

    bool isPrime(uint8_t num);
    void start();

    private:

    std::string ip_addr;
    unsigned int port;
    unsigned int socke = -1;
    
};

#endif