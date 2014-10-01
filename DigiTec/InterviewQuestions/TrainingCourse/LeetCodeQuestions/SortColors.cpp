#include "stdafx.h"

namespace SortColors
{
    class Solution
    {
    public:
        //use counting sort
        void sortColors(int A[], int n)
        {
            const int colors = 3;
            int indices[colors];

            for (int i = 0; i < colors; i++)
            {
                indices[i] = -1;
            }

            for (int i = 0; i < n; i++)
            {
                // 2 updates at 2, with value 2
                // 1 updates at 2, then 1
                int color = A[i];
                for (int i = (colors - 1); i >= color; i--)
                {
                    A[++indices[i]] = i;
                }
            }
        }
    };

    void RunTests()
    {
        Solution s;

        int s1[] = { 0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5 };
        s.sortColors(s1, _countof(s1));
    }
}