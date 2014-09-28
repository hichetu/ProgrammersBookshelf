#include "stdafx.h"

namespace RotateImage
{
    class Solution
    {
    public:
        void rotate(vector<vector<int> > &matrix)
        {
            int x1 = 0;
            int x2 = matrix.size() - 2;
            int y1 = 0;
            int y2 = matrix.size() / 2;

            for (int row = y1; row <= y2; row++)
            {
                for (int col = x1; col <= x2; col++)
                {
                    int pixel1 = matrix[row][col];
                    int pixel2 = matrix[row + col - x1][matrix.size() - 1 - row];
                    int pixel3 = matrix[matrix.size() - 1 - row][matrix.size() - 1 - col];
                    int pixel4 = matrix[matrix.size() - 1 - row - col + x1][row];

                    matrix[row][col] = pixel4;
                    matrix[row + col - x1][matrix.size() - 1 - row] = pixel1;
                    matrix[matrix.size() - 1 - row][matrix.size() - 1 - col] = pixel2;
                    matrix[matrix.size() - 1 - row - col + x1][row] = pixel3;
                }
                x1++; x2--;
            }
        }
    };

    void RunTests()
    {
        Solution s;
        vector<vector<int>> s1 = {
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9}
        };
        s.rotate(s1);

        vector<vector<int>> s2 = {
                { 1,  2,  3,  4  },
                { 5,  6,  7,  8  },
                { 9,  10, 11, 12 },
                { 13, 14, 15, 16 }
        };
        s.rotate(s2);
    }
}