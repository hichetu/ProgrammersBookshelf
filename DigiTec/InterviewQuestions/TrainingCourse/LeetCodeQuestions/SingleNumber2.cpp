#include "stdafx.h"

namespace SingleNumber2
{
    class Solution
    {
    public:
        int singleNumber(int A[], int n)
        {
            int bits1 = 0;
            int bits2 = 0;

            for (int i = 0; i < n; i++)
            {
                int threeBits = ~(bits2 & A[i]); // These are 3 bits, that become 0
                int twoBits = (bits1 & A[i] & ~bits2); // These are bits that need to move up to 2
                bits2 = ((bits2 & threeBits) | twoBits);
                bits1 = (bits1 ^ A[i] & threeBits);
            }
            return bits1;
        }

        int singleNumberEasy(int A[], int n)
        {
            int bitsArray[32] = { 0 };

            for (int i = 0; i < n; i++)
            {
                int curValue = A[i];
                int curBit = 0;

                while (curValue > 0)
                {
                    if (curValue & 1)
                    {
                        bitsArray[curBit] = ((bitsArray[curBit] + 1) % 3);
                    }
                    curValue >>= 1;
                    curBit += 1;
                }
            }

            int singleInteger = 0;
            for (int i = 0; i < 32; i++)
            {
                if (bitsArray[i] == 1)
                {
                    singleInteger += (1 << i);
                }
            }
            return singleInteger;
        }
    };

    void RunTests()
    {
        Solution s;

        int easy[] = { 1, 1, 1, 2 };
        _ASSERT(s.singleNumber(easy, _countof(easy)) == 2);

        int medium[] = { 1, 1, 1, 7, 7, 7, 9 };
        _ASSERT(s.singleNumber(medium, _countof(medium)) == 9);
    }
};