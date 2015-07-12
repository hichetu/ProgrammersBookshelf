#include "stdafx.h"

namespace DungeonGame
{
    class Solution
    {
    public:
        int calculateMinimumHP(vector<vector<int>>& dungeon)
        {
            /*
            // Work from the exit and determine, how much we would need to enter the room with in order to
            // satisfy the conditions of the game. Example for the first board. To exit, we need 1-(-5) or 6
            // health. So we need to solve backwards to get into the last room with 6 health.
            const size_t rows = dungeon.size();
            const size_t cols = dungeon[0].size();

            vector<vector<int>> solve(rows, vector<int>(cols));
            
            // To enter the last room, we need at least 1 health + whatever health we is required by the last room.
            solve[rows - 1][cols - 1] = max(1, 1 - dungeon[rows - 1][cols - 1]);
            
            // Then we fill out the columns of the last row. No sentinel can be used to make this easier :-(
            for (int col = cols - 2; col >= 0; col--)
            {
                solve[rows - 1][col] = max(1, solve[rows - 1][col + 1] - dungeon[rows - 1][col]);
            }
            // Then we fill out the last row
            for (int row = rows - 2; row >= 0; row--)
            {
                solve[row][cols-1] = max(1, solve[row+1][cols - 1] - dungeon[row][cols - 1]);
            }

            for (int row = rows - 2; row >= 0; row--)
            {
                for (int col = cols - 2; col >= 0; col--)
                {
                    int minRequiredHealthToExit = min(solve[row + 1][col], solve[row][col + 1]);
                    int healthConsumed = dungeon[row][col];
                    solve[row][col] = max(1, minRequiredHealthToExit - healthConsumed);
                }
            }
            return solve[0][0];
            */
            const int rowCount = dungeon.size();
            const int colCount = dungeon[0].size();

            vector<int> M(colCount + 1, INT_MAX);
            M[colCount - 1] = 1;
            for (int i = rowCount - 1; i >= 0; i--)
            {
                for (int j = colCount - 1; j >= 0; j--)
                {
                    M[j] = max(1, min(M[j], M[j + 1]) - dungeon[i][j]);
                }
            }
            return M[0];
        }
    };

    void RunTests()
    {
        Solution s;
        vector<vector<int>> d1 = {
            { -2, -3, 3 },
            { -5, -10, 1 },
            { 10, 30, -5 }
        };
        _ASSERT(s.calculateMinimumHP(d1) == 7);

        vector<vector<int>> d2 = {
            { 1, -3, 3 },
            { 0, -2, 0 },
            { -3, -3, -3 },
        };
        _ASSERT(s.calculateMinimumHP(d2) == 3);
    }
};