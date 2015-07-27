#include "stdafx.h"

namespace NumberOfOneDigit
{
    class Solution
    {
    public:
        int countDigitOne(int n)
        {
            if (n <= 0)
            {
                return 0;
            }
            if (n < 10)
            {
                return 1;
            }

            int result = 0;
            int factor = 1;
            int add = 1;

            int currentValue = n;
            if (currentValue % 10 > 0)
            {
                result = 1;
            }
            currentValue /= 10;

            while (currentValue != 0)
            {
                int currentDigit = currentValue % 10;
                currentValue /= 10;

                // Our factor is our accumulated quantity for how much a given scale is worth
                // For instance 10's are worth 1
                // 100's are worth 20
                result += (currentDigit*factor);

                // add is the base value of 1's for the current scale
                // 1, 10, 100, etc...
                add *= 10;

                if (currentDigit == 1)
                {
                    // If our current digit is a 1, such as 124, we want to add the number of 1's which is 124 % 100 = 24 + 1 = 25
                    result += n%add + 1;
                }
                else if (currentDigit > 1)
                {
                    // Otherwise we need to add all 100 such 1's
                    result += add;
                }

                // Increase our factor to account for one more scale, but also add in the overage or extra 1's from add
                factor = factor * 10 + add;
            }
            return result;
        }
    };

    void RunTests()
    {

    }
};