#ifndef DIVFINDERT_H
#define DIVFINDERT_H

#include <string>
#include "DivFinder.h"
#include <boost/multiprecision/cpp_int.hpp>

#define LARGEINT uint128_t

/* "Unsigned int twice as large as LARGEINT (bit-wise)" */
#define LARGEINT2X uint256_t

/* "Signed int made of twice the bits as LARGEINT2X" */
#define LARGESIGNED2X int512_t
// If factor has been called on a number x times, check to see if the number is prime
const unsigned int primecheck_depth = 10;

/******************************************************************************************
 * DivFinderSP - Used as a recursive calculator for prime numbers using Pollards Rho algorithm.
 *            A simple, recursive single process/thread version.
 *
 *  	   DivFinder(Const): 
 *  	   ~DivFinder(Dest):
 *
 *         PolRho - function that executes the stochastic Pollards' Rho algorithm for finding
 *                  divisors
 *         ifPrimeBF - uses brute force using 6k+-1 optimization to determine if a number is prime
 *
 *  	   Exceptions: sub-classes should throw a std::exception with the what string field
 *  	               populated for any issues.
 *
 *****************************************************************************************/

class DivFinderT : public DivFinder { 
   public:
      DivFinderT(LARGEINT input_value);
      virtual ~DivFinderT();

      virtual LARGEINT PolRho();

      bool isPrimeBF(LARGEINT n, LARGEINT &divisor);

   protected:

      void factor(LARGEINT n);


   private:

};

#endif
