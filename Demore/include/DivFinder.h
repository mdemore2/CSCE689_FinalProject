#ifndef POLRHO_H
#define POLRHO_H

#include <list>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include "config.h"

using namespace boost::multiprecision;

#define LARGEINT uint128_t

/* "Unsigned int twice as large as LARGEINT (bit-wise)" */
#define LARGEINT2X uint256_t

/* "Signed int made of twice the bits as LARGEINT2X" */
#define LARGESIGNED2X int512_t

/******************************************************************************************
 * DivFinder - Parent class for a set of single-process and multithreaded methods for finding
 *             prime numbers
 *
 *  	   DivFinder(Const):  Takes in an input value of LARGEINT (defined in configure.ac as
 *  	                      something like uint128_t)
 *  	   
 *  	   ~PFactors(Dest):  Doesn't do much currently
 *
 *  	   Exceptions: sub-classes should throw a std::exception with the what string field
 *  	               populated for any issues.
 *
 *****************************************************************************************/

class DivFinder { 
   public:
      DivFinder(LARGEINT input_value);
      virtual ~DivFinder();

      // Overload me 
      virtual void PolRho() = 0;

      LARGEINT getOrigVal() { return _orig_val; }

      virtual void combinePrimes(std::list<LARGEINT> &dest);
      LARGEINT calcPollardsRho(LARGEINT n);

      void setVerbose(int lvl);


   protected:

      LARGEINT2X modularPow(LARGEINT2X base, int exponent, LARGEINT2X modulus);

      std::list<LARGEINT> primes;
		
      int verbose = 0;

      // Do not forget, your constructor should call this constructor

   private:
      DivFinder() {}; // Prevent instantiation without calling initialization 

      LARGEINT _orig_val;

      // Stuff to be left alone
};

#endif
