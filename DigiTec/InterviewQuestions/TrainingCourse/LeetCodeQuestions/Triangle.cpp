#include "stdafx.h"

namespace Triangle
{
    class Solution
    {
    public:
        int minimumTotal(vector<vector<int> > &triangle)
        {
            int lastIndex = triangle.size() - 1;
            int* intValues = new int[triangle.size()];
            for (int i = 0; i < triangle.size(); i++)
            {
                intValues[i] = triangle[lastIndex][i];
            }

            for (int i = lastIndex - 1; i >= 0; i--)
            {
                for (int j = 0; j <= i; j++)
                {
                    intValues[j] = min(intValues[j], intValues[j + 1]) + triangle[i][j];
                }
            }
            return intValues[0];
        }
    };

    void RunTests()
    {
        vector<vector<int>> input{
            vector < int > {2},
            vector < int > {3, 4},
            vector < int > {6, 5, 7},
            vector < int > { 4, 1, 8, 3}
        };

        Solution s;
        int r1 = s.minimumTotal(input);
        _ASSERT(r1 == 11);
    }
};