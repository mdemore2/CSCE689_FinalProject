#include "DivFinder.h"
#include <cstdlib>
#include "config.h"
#include <iostream>


#define LARGEINT uint128_t

/* "Unsigned int twice as large as LARGEINT (bit-wise)" */
#define LARGEINT2X uint256_t

/* "Signed int made of twice the bits as LARGEINT2X" */
#define LARGESIGNED2X int512_t

int main(int argc, char *argv[]) {

    if(argc < 1)
    {
        std::cout << "Enter prime to factor.";
        return -1;
    }
    
    LARGEINT num = (LARGEINT)argv[0];
    DivFinder::calcPollardsRho(<LARGEINT> num);

    return 0;

}