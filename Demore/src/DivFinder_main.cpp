#include "DivFinder.h"
#include "DivFinderSP.h"
#include <cstdlib>
#include "config.h"
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std::chrono;


#define LARGEINT uint128_t

/* "Unsigned int twice as large as LARGEINT (bit-wise)" */
#define LARGEINT2X uint256_t

/* "Signed int made of twice the bits as LARGEINT2X" */
#define LARGESIGNED2X int512_t

int main(int argc, char *argv[]) {

    if(argc < 2)
    {
        std::cout << "Enter prime to factor.\n";
        return -1;
    }
    
    LARGEINT num;
    std::istringstream ss(argv[1]);
    if (!(ss >> num)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
    }   
    else if (!ss.eof()) {
    std::cerr << "Trailing characters after number: " << argv[1] << '\n';
    }
    
    DivFinderSP df = DivFinderSP(num);
    
    auto start = high_resolution_clock::now();
    LARGEINT divisor = df.PolRho();
    auto stop = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(stop - start);


    if(divisor == num)
    {
        std::cout << "Number is prime.\n";
    }
    else
    {
        std::cout << "Divisible by " << divisor << ".\n";
    }
    
    std::cout << "Completed in " << duration.count() << " microseconds.\n";

    return 0;

}