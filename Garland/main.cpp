#include <getopt.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "PrimeServer.hpp"
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


int main(int argc, char *argv[]) {

    // Check if the user entered a number
    //std::string num;
    LARGEINT num;
    try{
        std::istringstream ss(argv[1]);
        if (!(ss >> num)) {
            std::cerr << "Invalid number: " << argv[1] << '\n';
        }   
        else if (!ss.eof()) {
        std::cerr << "Trailing characters after number: " << argv[1] << '\n';
        }
    }catch(std::logic_error) {
        std::cout << "Please include a number to process." << std::endl;
        return -1;
    }

    // TODO: Add in number checking
    std::cout << "Starting Server Threads...\n";
    std::string ip_addr = "127.0.0.1";
    PrimeServer* server1 = new PrimeServer(ip_addr, 9997, num);
    PrimeServer* server2 = new PrimeServer(ip_addr, 9998, num);
    PrimeServer* server3 = new PrimeServer(ip_addr, 9999, num);

    std::thread thd1(&PrimeServer::start, server1);
    std::thread thd2(&PrimeServer::start, server2);
    std::thread thd3(&PrimeServer::start, server3);

    thd1.join();
    thd2.join();
    thd3.join();
    
    std::cout << "Processing " << num << " with 3 nodes\n";
    
    // TODO: Start different processing nodes
}