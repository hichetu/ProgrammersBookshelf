#include "stdafx.h"

namespace BestTimeToBuyAndSellStock3
{
    class Solution
    {
    public:
        int maxProfit(vector<int> &prices)
        {
            if (prices.size() < 2)
            {
                return 0;
            }
            
            vector<int> maxOnDay;
            maxOnDay.resize(prices.size());
            maxOnDay[0] = 0;

            int curMin = prices[0];
            for (size_t i = 1; i < prices.size(); i++)
            {
                int curValue = prices[i];
                if (curValue > curMin)
                {
                    maxOnDay[i] = max(maxOnDay[i - 1], curValue - curMin);
                }
                else
                {
                    maxOnDay[i] = maxOnDay[i - 1];
                    curMin = curValue;
                }
            }

            vector<int> maxAfterDay;
            maxAfterDay.resize(prices.size());
            maxAfterDay[maxAfterDay.size() - 1] = 0;
            int curMax = prices[prices.size() - 1];
            for (int i = prices.size() - 2; i >= 0; i--)
            {
                int curValue = prices[i];
                if (curValue < curMax)
                {
                    maxAfterDay[i] = max(maxAfterDay[i + 1], curMax - curValue);
                }
                else
                {
                    maxAfterDay[i] = maxAfterDay[i + 1];
                    curMax = curValue;
                }
            }

            int profit = 0;
            for (size_t i = 0; i < prices.size(); i++)
            {
                profit = max(profit, maxOnDay[i] + maxAfterDay[i]);
            }
            return profit;
        }
    };

    void RunTests()
    {
        vector<int> empty = {};
        vector<int> single = { 1 };
        vector<int> decreasing = { 5, 4, 3, 2, 1 };
        vector<int> increasing = { 1, 2, 3, 4, 5 };
        vector<int> overlapping = { 0, 2, 4, 4, 3, 6, 8, 6 };
        vector<int> overlappingRise = { 0, 2, 4, 4, 3, 6, 8, 6, 4, 6 };

        Solution s;
        _ASSERT(s.maxProfit(empty) == 0);
        _ASSERT(s.maxProfit(single) == 0);
        _ASSERT(s.maxProfit(decreasing) == 0);
        _ASSERT(s.maxProfit(increasing) == 4);
        _ASSERT(s.maxProfit(overlapping) == 9);
        _ASSERT(s.maxProfit(overlappingRise) == 10);
    }
};