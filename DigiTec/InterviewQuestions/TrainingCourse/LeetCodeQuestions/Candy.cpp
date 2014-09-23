#include "stdafx.h"

namespace Candy
{
    class Solution
    {
    public:
        int candy(vector<int> &ratings)
        {
            // Initialize the candy vector to all 1's, all children must get at least one candy.
            vector<int> candy(ratings.size(), 1);

            // Compare all pairs of ratings incrementing candy as necessary by comparing
            // the child on the left to the right. This means if we have:
            // Ratings of 1,2,3, we'll end up with candy 1,2,3
            // Ratings of 3,2,1, we'll end up with candy 1,1,1
            for (int i = 0; i < ratings.size() - 1; i++)
            {
                if (ratings[i + 1] > ratings[i])
                {
                    candy[i + 1] = candy[i] + 1;
                }
            }
            // So now we compute candy again going right to left
            // Ratings of 1,2,3, will not pass the test and so we'll retain original candy 1,2,3
            // Ratings of 3,2,1, will now increment 2,1 to be 2, and 3,2 to be 2+1 or 3 and candy will be 3,2,1
            for (int i = ratings.size() - 1; i > 0; i--)
            {
                if (ratings[i - 1] > ratings[i])
                {
                    // We either need to keep our previous value or increment
                    candy[i - 1] = max(candy[i - 1], candy[i] + 1);
                }
            }

            int totalCandy = 0;
            for (const int& kid : candy)
            {
                totalCandy += kid;
            }
            return totalCandy;
        }
    };
}