#ifndef PRIMESERVER_H
#define PRIMESERVER_H

#include <stdint.h>
#include <string>
#include <thread>

#include "DivFinder.h"
#include "DivFinderT.h"
#include <cstdlib>
#include "config.h"
#include <chrono>

#define LARGEINT uint128_t

/* "Unsigned int twice as large as LARGEINT (bit-wise)" */
#define LARGEINT2X uint256_t

/* "Signed int made of twice the bits as LARGEINT2X" */
#define LARGESIGNED2X int512_t


class PrimeServer
{
    public:
    PrimeServer(std::string ip_addr, unsigned int port, LARGEINT prime);

    void start();
    void checkPrime();
    bool sendMsg();
    void startServer();

    private:

    std::string ip_addr;
    unsigned int port;
    LARGEINT prime;
    int sock = -1;
    bool is_prime = false, rec_msg = false, checking_prime = true;
    
};

#endif