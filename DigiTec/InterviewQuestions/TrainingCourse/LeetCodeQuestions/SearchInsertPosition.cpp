#include "stdafx.h"

namespace SearchInsertPosition
{
    class Solution
    {
    public:
        int searchInsert(int A[], int n, int target)
        {
            int lo = 0;
            int hi = n - 1;
            while (lo <= hi)
            {
                int mid = (hi + lo) / 2;
                if (A[mid] < target)
                {
                    lo = mid + 1;
                }
                else if (A[mid] > target)
                {
                    hi = mid - 1;
                }
                else
                {
                    return mid;
                }
            }
            return lo;
        }
    };

    void RunTests()
    {
        Solution s;
        int test1[] = { 1 };

        _ASSERT(s.searchInsert(test1, _countof(test1), 0) == 0);
        _ASSERT(s.searchInsert(test1, _countof(test1), 1) == 0);
        _ASSERT(s.searchInsert(test1, _countof(test1), 2) == 1);

        int test2[] = { 1, 3, 5, 6 };
        _ASSERT(s.searchInsert(test2, _countof(test2), 3) == 1);
        _ASSERT(s.searchInsert(test2, _countof(test2), 4) == 2);
        _ASSERT(s.searchInsert(test2, _countof(test2), 5) == 2);
        _ASSERT(s.searchInsert(test2, _countof(test2), 7) == 4);
    }
}