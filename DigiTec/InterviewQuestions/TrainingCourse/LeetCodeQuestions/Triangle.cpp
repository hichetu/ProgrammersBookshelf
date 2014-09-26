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

        int recurse(vector<vector<int>> &triangle, int row, int col)
        {
            if (row == (triangle.size() - 1))
            {
                return triangle[row][col];
            }
            return min(recurse(triangle, row + 1, col), recurse(triangle, row + 1, col + 1)) + triangle[row][col];
        }

        int topDown(vector<vector<int>> &triangle)
        {
            map<pair<int, int>, int> scratch;
            return minPath(triangle, pair<int, int>( 0, 0 ), scratch);
        }

        int minPath(vector<vector<int>> &triangle, pair<int, int>& cell, map<pair<int, int>, int> &scratch)
        {
            if (cell.first == (triangle.size() - 1))
            {
                return triangle[cell.first][cell.second];
            }
            if (scratch.count(cell) == 0)
            {
                scratch[cell] = min(minPath(triangle, pair<int, int>(cell.first + 1, cell.second), scratch), minPath(triangle, pair<int, int>(cell.first + 1, cell.second + 1), scratch)) + triangle[cell.first][cell.second];
            }
            return scratch[cell];
        }
    };

    void RunTests()
    {
        vector<vector<int>> input{
            vector < int > {2},
            vector < int > {3, 4},
            vector < int > {6, 5, 7},
            vector < int > {4, 1, 8, 3}
        };

        Solution s;
        int r1 = s.minimumTotal(input);
        _ASSERT(r1 == 11);
        _ASSERT(r1 == s.topDown(input));
        _ASSERT(r1 == s.recurse(input, 0, 0));
    }
};