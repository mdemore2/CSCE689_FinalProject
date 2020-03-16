#include <getopt.h>
#include <iostream>
#include <thread>
#include "PrimeServer.hpp"

int main(int argc, char *argv[]) {

    // Check if the user entered a number
    std::string num;
    try{
        num = std::string(argv[1]);
    } catch(std::logic_error) {
        std::cout << "Please include a number to process." << std::endl;
        return -1;
    }

    // TODO: Add in number checking
    std::cout << "Starting Server Threads...\n";
    std::string ip_addr = "127.0.0.1";
    PrimeServer* server1 = new PrimeServer(ip_addr, 9997, 10);
    PrimeServer* server2 = new PrimeServer(ip_addr, 9998, 10);
    PrimeServer* server3 = new PrimeServer(ip_addr, 9999, 10);

    std::thread thd1(&PrimeServer::start, server1);
    std::thread thd2(&PrimeServer::start, server2);
    std::thread thd3(&PrimeServer::start, server3);

    thd1.join();
    thd2.join();
    thd3.join();
    
    std::cout << "Processing " << num << " with 3 nodes\n";
    
    // TODO: Start different processing nodes
}