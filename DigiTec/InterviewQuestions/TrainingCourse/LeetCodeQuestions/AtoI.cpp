#include "stdafx.h"

namespace AtoI
{
    class Solution
    {
    public:
        int toDigit(const char ch)
        {
            switch (ch)
            {
            case '0': return 0;
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            case '8': return 8;
            case '9': return 9;
            }
            return -1;
        }

        int atoi(const char *str)
        {
            bool positive = true;
            int accum = 0;
            if (str != nullptr)
            {
                while (*str == ' ')
                {
                    str++;
                }
                if (*str == '+')
                {
                    str++;
                }
                else if (*str == '-')
                {
                    positive = false;
                    str++;
                }
                int value = toDigit(*str);
                if (value != -1 && !positive)
                {
                    str++;
                    accum -= value;
                }

                value = toDigit(*str++);
                while (value != -1)
                {
                    if (positive)
                    {
                        if (accum > (INT_MAX / 10))
                        {
                            accum = INT_MAX;
                            break;
                        }
                        accum *= 10;
                        accum += value;
                        if (accum < 0)
                        {
                            accum = INT_MAX;
                            break;
                        }
                    }
                    else
                    {
                        if (accum < (INT_MIN / 10))
                        {
                            accum = INT_MIN;
                            break;
                        }
                        accum *= 10;
                        accum -= value;
                        if (accum > 0)
                        {
                            accum = INT_MIN;
                            break;
                        }
                    }
                    value = toDigit(*str++);
                }
            }
            return accum;
        }
    };

    void RunTests()
    {
        Solution s;

        // Integer maxes
        const char* intMax = "2147483647";
        const char* intMaxPos = "+2147483647";
        const char* intMaxPosWS = "   +2147483647";
        const char* intMaxPosGarbage = "   +2147483647abcd";

        _ASSERT(s.atoi(intMax) == INT_MAX);
        _ASSERT(s.atoi(intMaxPos) == INT_MAX);
        _ASSERT(s.atoi(intMaxPosWS) == INT_MAX);
        _ASSERT(s.atoi(intMaxPosGarbage) == INT_MAX);

        // Integer maxes under/over
        const char* intMaxPlusOne = "2147483648";
        const char* intMaxMinusOne = "2147483646";
        _ASSERT(s.atoi(intMaxPlusOne) == INT_MAX);
        _ASSERT(s.atoi(intMaxMinusOne) == (INT_MAX-1));

        // Integer mins
        const char* intMinNeg = "-2147483648";
        const char* intMinNegWS = "   -2147483648";
        const char* intMinNegGarbage = "    -2147483648abcde";

        _ASSERT(s.atoi(intMinNeg) == INT_MIN);
        _ASSERT(s.atoi(intMinNegWS) == INT_MIN);
        _ASSERT(s.atoi(intMinNegGarbage) == INT_MIN);

        // Integer mins under/over
        const char* intMinNegMinusOne = "-2147483649";
        const char* intMinNegPlusOne = "-2147483647";

        _ASSERT(s.atoi(intMinNegMinusOne) == INT_MIN);
        _ASSERT(s.atoi(intMinNegPlusOne) == (INT_MIN + 1));

        // Judge failures
        const char* intJudge1 = "    10522545459";
        _ASSERT(s.atoi(intJudge1) == INT_MAX);
    }
};