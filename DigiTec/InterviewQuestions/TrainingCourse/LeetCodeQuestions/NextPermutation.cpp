#include "stdafx.h"

namespace NextPermutation
{
    class Solution
    {
    public:
        void nextPermutation(vector<int> &num)
        {
            for (int i = num.size() - 1; i > 0; i--)
            {
                if (num[i - 1] < num[i])
                {
                    pair<int, int> p = findMinGreater(num, num[i - 1], i);

                    int swap = num[p.first];
                    num[p.first] = num[i - 1];
                    num[i - 1] = swap;

                    sort(num.begin() + i, num.end());
                    return;
                }
            }
            reverse(num.begin(), num.end());
        }
        pair<int, int> findMinGreater(vector<int>& num, int min, int start)
        {
            pair<int, int> p = { start, num[start] };
            for (int i = start + 1; i < num.size(); i++)
            {
                if (num[i] > min && num[i] < p.second)
                {
                    p.first = i;
                    p.second = num[i];
                }
            }
            return p;
        }
    };

    void RunTests()
    {
        Solution s;
        vector<int> s1 = { 1, 3, 2 };
        s.nextPermutation(s1);

        vector<int> s2 = { 1, 1, 5 };
        s.nextPermutation(s2);
    }
}