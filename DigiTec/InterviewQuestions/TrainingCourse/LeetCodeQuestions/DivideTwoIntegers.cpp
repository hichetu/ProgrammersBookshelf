#include "stdafx.h"

namespace DivideTwoIntegers
{
    class Solution
    {
    public:
        int divide(int dividend, int divisor)
        {
            int times = 0;
            bool flip = false;

            unsigned int uDivisor = (divisor < 0) ? -divisor : divisor;
            unsigned int uDividend = (dividend < 0) ? -dividend : dividend;
            
            if (divisor < 0)
            {
                flip = !flip;
            }
            if (dividend < 0)
            {
                flip = !flip;
            }

            unsigned int scaleCount = 1;
            unsigned int scaleValue = uDivisor;
            while (uDividend > 0 && uDividend >= uDivisor)
            {
                if (scaleValue > uDividend)
                {
                    while (scaleValue > uDividend)
                    {
                        scaleCount >>= 1;
                        scaleValue >>= 1;
                    }
                }
                else
                {
                    while ((scaleValue << 1) != 0 && (scaleValue << 1) < uDividend)
                    {
                        scaleCount <<= 1;
                        scaleValue <<= 1;
                    }
                }

                uDividend -= scaleValue;
                times += scaleCount;
            }
            if (flip)
            {
                times = -times;
            }
            return times;
        }
    };

    void RunTests()
    {

        Solution s;
        _ASSERT(s.divide(1, -1) == -1);
        _ASSERT(s.divide(-1, 1) == -1);
        _ASSERT(s.divide(INT_MIN, 1) == INT_MIN);
        _ASSERT(s.divide(INT_MIN, INT_MIN) == 1);
        _ASSERT(s.divide(INT_MAX, 1) == INT_MAX);
        _ASSERT(s.divide(2147483647, -1354984617) == -1);
    }
}