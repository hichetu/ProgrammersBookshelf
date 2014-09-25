#include "stdafx.h"

namespace BestTimeToBuyAndSellStock2
{
    class Solution
    {
    public:
        int maxProfit(vector<int> &prices)
        {
            int curProfit = 0;
            int lastPeak = 0;
            int curMin = 0;
            if (prices.size() > 1)
            {
                lastPeak = prices[0];
                curMin = prices[0];
                for (int i = 1; i < prices.size(); i++)
                {
                    int curPrice = prices[i];
                    if (curPrice < lastPeak)
                    {
                        curProfit += lastPeak - curMin;
                        curMin = curPrice;
                        lastPeak = curPrice;
                    }
                    else
                    {
                        lastPeak = curPrice;
                    }
                }
            }
            curProfit += lastPeak - curMin;
            return curProfit;
        }
    };

    void RunTests()
    {
        vector<int> emptyTest = {};
        vector<int> singleTest = { 5 };
        vector<int> basicTest = { 1, 4, 2 };

        Solution s;
        _ASSERT(s.maxProfit(emptyTest) == 0);
        _ASSERT(s.maxProfit(singleTest) == 0);
        _ASSERT(s.maxProfit(basicTest) == 3);
    }
};