#include "stdafx.h"

namespace MergeSortedArray
{
    class Solution
    {
    public:
        void merge(int A[], int m, int B[], int n)
        {
            int offset = (n + m) - 1;

            m--; n--;
            while (m >= 0 && n >= 0)
            {
                if (A[m] > B[n])
                {
                    A[offset--] = A[m--];
                }
                else
                {
                    A[offset--] = B[n--];
                }
            }
            while (n >= 0)
            {
                A[offset--] = B[n--];
            }
        }
    };

    void RunTests()
    {
        Solution s;
        int s1[] = { 0, 0, 0, 0 };
        int s2[] = { 1, 0, 0, 0 };
        s.merge(s1, 0, s2, 1);
    }
}