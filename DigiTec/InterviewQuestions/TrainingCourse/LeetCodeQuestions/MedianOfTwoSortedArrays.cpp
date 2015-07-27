#include "stdafx.h"

namespace MedianOfTwoSortedArrays
{
    class Solution
    {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
        {
            // Assume value is in the left-most array
            return findMedianInLeftArray(nums1, nums2, 0, nums1.size() - 1);
        }
        double findMedianInLeftArray(const vector<int>&nums1, const vector<int>& nums2, int leftBound, int rightBound)
        {
            // We've swapped over, so assume the value in the rightmost array
            if (leftBound > rightBound)
            {
                // We've consumed A so our left is now offset by our mid-point less the size of our first array
                // Our rightmost is our own size or the mid-point whichever is lesser.
                return findMedianInLeftArray(nums2, nums1, 
                    max(0, static_cast<int>((nums1.size() + nums2.size()) / 2 - nums1.size())), 
                    min(nums2.size() - 1, (nums1.size() + nums2.size()) / 2));
            }

            // Computed our current index point for the median in nums1
            int midPoint = (leftBound + rightBound + 1) / 2;
            
            // Compute our offset such that midPoint + offsetPoint is the midPoint for BOTH arrays.
            int offsetPoint = (nums1.size() + nums2.size()) / 2 - midPoint - 1;
            
            // This is our "binary search" core
            if (offsetPoint >= 0 && (offsetPoint >= nums2.size() || nums1[midPoint] < nums2[offsetPoint]))
            {
                // We will continue searching in our right sub-tree until offsetPoint is less than 0 meaning we found
                // the value in nums1.
                return findMedianInLeftArray(nums1, nums2, midPoint + 1, rightBound);
            }
            else if (offsetPoint < static_cast<int>(nums2.size()) - 1 && (offsetPoint < -1 || nums1[midPoint] > nums2[offsetPoint + 1]))
            {
                // Similarly we will continue searching in our left sub-tree if we are larger than our next
                // higher offset point, since it means we are still too large to be the median.
                return findMedianInLeftArray(nums1, nums2, leftBound, midPoint - 1);
            }
            else
            {
                // We found our value so return it if we are "odd"
                if ((nums1.size() + nums2.size()) & 1)
                {
                    return nums1[midPoint];
                }
                else if (offsetPoint < 0)
                {
                    // We are even and we are the only array, so return an average directly.
                    return (nums1[midPoint] + nums1[midPoint - 1]) / static_cast<double>(2.0);
                }
                else if (midPoint > 0)
                {
                    // We are even and we are not at the start of our array, so we need to check both arrays
                    // for our second value.
                    return (nums1[midPoint] + max(nums2[offsetPoint], nums1[midPoint - 1])) / static_cast<double>(2.0);
                }
                else
                {
                    // We are at the start of our array, so we need to average that with our offsetpoint in our second array.
                    return (nums1[midPoint] + nums2[offsetPoint]) / static_cast<double>(2.0);
                }
            }
        }
    };

    void RunTests()
    {
        Solution s;

        vector<int> p1_v1 = { 1, 2 };
        vector<int> p1_v2 = { 1, 2, 3 };

        _ASSERT(s.findMedianSortedArrays(p1_v1, p1_v2) == 2);

        vector<int> p1_1_v1 = { 1, 2, 3 };
        vector<int> p1_1_v2 = { 1, 2 };

        _ASSERT(s.findMedianSortedArrays(p1_1_v1, p1_1_v2) == 2);

        vector<int> p2_v1 = { 1, 2, 3};
        vector<int> p2_v2 = { 4, 5, 6 };

        _ASSERT(s.findMedianSortedArrays(p2_v1, p2_v2) == 3.5);

        vector<int> p3_v1 = { 1, 2, 3 };
        vector<int> p3_v2 = { 4, 5, 6, 7 };
        _ASSERT(s.findMedianSortedArrays(p3_v1, p3_v2) == 4);

        vector<int> p4_v1 = { 4 };
        vector<int> p4_v2 = { 1, 2, 3, 5, 6, 7 };
        _ASSERT(s.findMedianSortedArrays(p4_v1, p4_v2) == 4);

        vector<int> p5_v1 = {};
        vector<int> p5_v2 = { 2, 3 };
        _ASSERT(s.findMedianSortedArrays(p5_v1, p5_v2) == 2.5);

        vector<int> p5_1_v1 = { 3, 4 };
        vector<int> p5_1_v2 = { };
        _ASSERT(s.findMedianSortedArrays(p5_1_v1, p5_1_v2) == 3.5);

        vector<int> p5_2_v1 = { 3, 4, 5, 6, 7, 8 };
        vector<int> p5_2_v2 = {};
        _ASSERT(s.findMedianSortedArrays(p5_2_v1, p5_2_v2) == 5.5);

        vector<int> p6_v1 = { 4 };
        vector<int> p6_v2 = { 1, 2, 3, 4, 5, 6, 7 };
        _ASSERT(s.findMedianSortedArrays(p6_v1, p6_v2) == 4);

        vector<int> p7_v1 = { 3, 4, 6, 7, 8 };
        vector<int> p7_v2 = { 1, 2, 5 };
        _ASSERT(s.findMedianSortedArrays(p7_v1, p7_v2) == 4.5);

        vector<int> p8_v1 = { 100000 };
        vector<int> p8_v2 = { 100001 };
        _ASSERT(s.findMedianSortedArrays(p8_v1, p8_v2) == 100000.5);

        vector<int> p9_v1 = { 1 };
        vector<int> p9_v2 = { 2, 3 };
        _ASSERT(s.findMedianSortedArrays(p9_v1, p9_v2) == 2);

        vector<int> p10_v1 = { 1, 2, 3, 4, 5, 7, 8, 9, 10 };
        vector<int> p10_v2 = { 6 };
        _ASSERT(s.findMedianSortedArrays(p10_v1, p10_v2) == 5.5);
    }
}