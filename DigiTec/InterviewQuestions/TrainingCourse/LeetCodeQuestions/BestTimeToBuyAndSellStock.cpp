#include "stdafx.h"

namespace BestTimeToBuyAndSellStock
{
    class Solution
    {
    public:
        int maxProfit(vector<int> &prices)
        {
            int curMin = numeric_limits<int>::max();
            int maxProfit = 0;

            for (const int& i : prices)
            {
                if (i >= curMin)
                {
                    maxProfit = max(maxProfit, i - curMin);
                }
                else
                {
                    curMin = i;
                }
            }
            return maxProfit;
        }
    };

    void RunTests()
    {
    }
};