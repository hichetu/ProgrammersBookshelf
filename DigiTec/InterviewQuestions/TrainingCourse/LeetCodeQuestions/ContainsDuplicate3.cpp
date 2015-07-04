#include "stdafx.h"

namespace ContainsDuplicate3
{
    class Solution
    {
    public:
        bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
        {
            const int len = nums.size();
            if (k <= 0 || t < 0 || len <= 1)
            {
                return false;
            }

            std::set<int> previous;
            previous.insert(nums[0]);

            int i;
            for (i = 1; i < len && i <= k; i++)
            {
                const int currentValue = nums[i];
                auto it = previous.lower_bound(currentValue - t);
                if (it != previous.end())
                {
                    int diff = currentValue - *it;
                    if (diff >= -t && diff <= t)
                    {
                        return true;
                    }
                }
                previous.insert(currentValue);
            }
            for (int removeAt = 0; i < len; i++)
            {
                previous.erase(nums[removeAt++]);

                const int currentValue = nums[i];
                auto it = previous.lower_bound(currentValue - t);
                if (it != previous.end())
                {
                    int diff = currentValue - *it;
                    if (diff >= -t && diff <= t)
                    {
                        return true;
                    }
                }
                previous.insert(currentValue);
            }
            return false;
        }
    };

    void RunTests()
    {

        Solution s;
        vector<int> v1 = { 1, 3, 1 };
        _ASSERT(s.containsNearbyAlmostDuplicate(v1, 1, 1) == false);

        vector<int> v2 = { 0, 2147483647 };
        _ASSERT(s.containsNearbyAlmostDuplicate(v2, 1, 2147483647) == true);

        vector<int> v3 = { 2, 0, -2, 2 };
        _ASSERT(s.containsNearbyAlmostDuplicate(v3, 2, 1) == false);
    }
}