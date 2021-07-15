// ---------------------------------------------------------------------------
// PrimeCPP.cpp : Dave's Garage Prime Sieve in C++ - No warranty for anything!
// ---------------------------------------------------------------------------

#define _XOPEN_SOURCE_EXTENDED 1

#include <stdio.h>
#include <ctime>
#include <iostream>
#include <bitset>
#include <map>
#include <cstring>
#include <cmath>
#include <vector>
#include <sys/time.h>
#include <string>

using namespace std;

class prime_sieve
{
  private:

      long sieveSize;
      unsigned char* rawbits;

      bool validateResults()
      {
    	  std::map<long long, int> resultsDictionary;
	  	  resultsDictionary[          10LL ] =  4         ;            // Historical data for validating our results - the number of primes
		  resultsDictionary[         100LL ] =  25        ;            // to be found under some limit, such as 168 primes under 1000
		  resultsDictionary[        1000LL ] =  168       ;
		  resultsDictionary[       10000LL ] =  1229      ;
		  resultsDictionary[      100000LL ] =  9592      ;
		  resultsDictionary[     1000000LL ] =  78498     ;
		  resultsDictionary[    10000000LL ] =  664579    ;
		  resultsDictionary[   100000000LL ] =  5761455   ;
		  resultsDictionary[  1000000000LL ] =  50847534  ;
		  resultsDictionary[ 10000000000LL ] =  455052511 ;

          auto result = resultsDictionary.find(sieveSize);
          if (resultsDictionary.end() == result)
              return false;
          return result->second == countPrimes();
      }

      bool GetBit(unsigned int index)
      {
          if (index % 2 == 0)
              return false;
          index = index / 2;
          return ((rawbits[index / 8]) & (1 << (index % 8))) != 0;
      }

      void ClearBit(unsigned int index)
      {
          index = index / 2;
          rawbits[index / 8] &= ~(1 << (index % 8));
      }

   public:

      prime_sieve(long n)
          : sieveSize(n)
      {
          rawbits = (unsigned char*)malloc(n / 8 + 1);
          if (rawbits)
              memset(rawbits, 0xff, n / 8 + 1);
      }

      ~prime_sieve()
      {
          free(rawbits);
      }

      void runSieve()
      {
          int factor = 3;
          int q = (int) sqrt((double)sieveSize);

          while (factor <= q)
          {
              for (int num = factor; num < sieveSize; num += 2)
              {
                  if (GetBit(num))
                  {
                      factor = num;
                      break;
                  }
              }
              for (int num = factor * factor; num < sieveSize; num += factor * 2)
                  ClearBit(num);

              factor += 2;
          }
      }

      void printResults(bool showResults, double duration, int passes)
      {
          if (showResults)
              printf("2, ");

          int count = (sieveSize >= 2);                             // Starting count (2 is prime)
          for (int num = 3; num <= sieveSize; num+=2)
          {
              if (GetBit(num))
              {
                  if (showResults)
                      printf("%d, ", num);
                  count++;
              }
          }

          if (showResults)
              printf("\n");

          printf("Passes: %d, Time: %lf, Avg: %lf, Limit: %ld, Count1: %d, Count2: %d, Valid: %d\n",
                 passes,
                 duration,
                 duration / passes,
                 sieveSize,
                 count,
                 countPrimes(),
                 validateResults());

          // Following 2 lines added by rbergen to conform to drag race output format
          printf("\n");
          printf("davepl;%d;%f;1;algorithm=base,faithful=yes,bits=1\n", passes, duration);
      }

      int countPrimes()
      {
          int count =  (sieveSize >= 2);;
          for (int i = 3; i < sieveSize; i+=2)
              if (GetBit(i))
                  count++;
          return count;
      }
};

int main()
{
    auto passes = 0;
    //auto tStart = steady_clock::now();

    timeval tim;
    gettimeofday(&tim,NULL);

    double tstart = tim.tv_sec + ((double)tim.tv_usec/1000000);


    while (true)
    {
        prime_sieve sieve(1000000L);
        sieve.runSieve();
        passes++;
        timeval now;
        gettimeofday(&now,NULL);
        double tnow = now.tv_sec + ((double)now.tv_usec/1000000);

        if (tnow - tstart >= 5)
        {
            sieve.printResults(false, (tnow - tstart), passes);
            break;
        }
    }
}
