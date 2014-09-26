#include "stdafx.h"

namespace MaximumProductSubarray
{
    class Solution
    {
    public:
        int maxProduct(int A[], int n)
        {
            int currentMax = 0;
            if (n > 0)
            {
                currentMax = A[0];
                int currentValue = 1;
                int negativeSeries1 = 1;
                int negativeSeries2 = 0;

                for (int i = 0; i < n; i++)
                {
                    currentValue *= A[i];
                    negativeSeries1 *= A[i];
                    negativeSeries2 *= A[i];
                    currentMax = max(negativeSeries1, max(currentValue, currentMax));
                        
                    if (currentValue == 0)
                    {
                        currentValue = 1;
                        negativeSeries1 = 1;
                        negativeSeries2 = 0;
                    }
                    else
                    {
                        if (negativeSeries2 != 0)
                        {
                            currentMax = max(negativeSeries2, currentMax);
                        }
                        if (currentValue < 0)
                        {
                            currentValue = 1;
                            if (negativeSeries2 == 0)
                            {
                                negativeSeries2 = 1;
                            }
                        }
                    }
                }
            }
            return currentMax;
        }
    };

    void RunTests()
    {
        Solution s;

        // Base tests
        int singleArrayPos[] = { 20 };
        int singleArrayNeg[] = { -20 };
        int twoArrayPos[] = { 5, 4 };
        int twoArrayNeg[] = { -5, -4 };
        _ASSERT(s.maxProduct(nullptr, 0) == 0);
        _ASSERT(s.maxProduct(singleArrayPos, _countof(singleArrayPos)) == 20);
        _ASSERT(s.maxProduct(singleArrayNeg, _countof(singleArrayNeg)) == -20);
        _ASSERT(s.maxProduct(twoArrayPos, _countof(twoArrayPos)) == 20);
        _ASSERT(s.maxProduct(twoArrayNeg, _countof(twoArrayNeg)) == 20);

        // 0's
        int zero1[] = { 0 };
        int zero2[] = { 0, 10 };
        int zero3[] = { 10, 0 };
        int zero4[] = { -2, 0, -1 };
        _ASSERT(s.maxProduct(zero1, _countof(zero1)) == 0);
        _ASSERT(s.maxProduct(zero2, _countof(zero2)) == 10);
        _ASSERT(s.maxProduct(zero3, _countof(zero3)) == 10);
        _ASSERT(s.maxProduct(zero4, _countof(zero4)) == 0);

        // Single negative
        int singleNeg1[] = { 3, -1, 4 };
        _ASSERT(s.maxProduct(singleNeg1, _countof(singleNeg1)) == 4);

        int sample1[] = { 2, 3, -2, 4 };
        _ASSERT(s.maxProduct(sample1, _countof(sample1)) == 6);

        // Judge Tests
        int judge1[] = { -2, -3, 7 };
        _ASSERT(s.maxProduct(judge1, _countof(judge1)) == 42);

        int judge2[] = { 2, -5, -2, -4, 3 };
        _ASSERT(s.maxProduct(judge2, _countof(judge2)) == 24);

        int judge3[] = { 3, -2, -3, -3, 1, 3, 0 };
        _ASSERT(s.maxProduct(judge3, _countof(judge3)) == 27);

        int judge4[] = { 3, -2, -3, 3, -1, 0, 1 };
        _ASSERT(s.maxProduct(judge4, _countof(judge4)) == 54);

        int judgeAlt4[] = { 3, -2, 1, -3, 3, -1, 0, 1 };
        _ASSERT(s.maxProduct(judgeAlt4, _countof(judgeAlt4)) == 54);

        int judge5[] = { 1, 0, -1, 2, 3, -5, -2 };
        _ASSERT(s.maxProduct(judge5, _countof(judge5)) == 60);
    }
}