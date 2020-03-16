#ifndef PRIMESERVER_H
#define PRIMESERVER_H

#include <stdint.h>
#include <string>

class PrimeServer
{
    public:
    PrimeServer(std::string ip_addr, unsigned int port, unsigned int prime);

    void start();

    private:
    bool checkPrime();
    bool sendMsg();

    std::string ip_addr;
    unsigned int port, prime;
    int sock = -1;
    bool is_prime = false;
    
};

#endif