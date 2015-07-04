#include "stdafx.h"

namespace CountPrimes
{
    class Solution
    {
    public:
        int countPrimes(int n)
        {
            if (n < 3)
            {
                return 0;
            }
            
            vector<int> numbers(n, 0);
            int prime = 2;
            int primes = 0;
            for (; prime < n / 2 + 1;)
            {
                for (int k = prime + prime; k < n; k += prime)
                {
                    // Composites
                    numbers[k] = 1;
                }

                for (prime += 1; prime < n; prime++)
                {
                    // Primes
                    if (numbers[prime] == 0)
                    {
                        primes++;
                        break;
                    }
                }
            }

            for (; prime < n; prime++)
            {
                if (numbers[prime] == 0)
                {
                    primes++;
                }
            }
            return primes;
        }
    };

    void RunTests()
    {
        Solution s;
        _ASSERT(s.countPrimes(2) == 0);
        _ASSERT(s.countPrimes(3) == 1);
        _ASSERT(s.countPrimes(4) == 2);
        _ASSERT(s.countPrimes(5) == 2);
        _ASSERT(s.countPrimes(6) == 3);
        _ASSERT(s.countPrimes(7) == 3);
        _ASSERT(s.countPrimes(8) == 4);
    }
}