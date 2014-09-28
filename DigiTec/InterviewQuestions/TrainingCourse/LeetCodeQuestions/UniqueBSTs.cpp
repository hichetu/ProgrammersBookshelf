#include "stdafx.h"

namespace UniqueBSTs
{
    class Solution
    {
    public:
        int numTrees(int n)
        {
            unsigned long long num = 1;
            for (int i = 2 * n; i > n + 1; i--)
            {
                num *= i;
            }
            unsigned long long denom = 1;
            for (int i = 2; i <= n; i++)
            {
                denom *= i;
            }
            return (int)(num / denom);
        }
    };
}