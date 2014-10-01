#include "stdafx.h"

namespace SetMatrixZeroes
{
    class Solution
    {
    public:
        void setZeroes(vector<vector<int> > &matrix)
        {
            if (matrix.size() > 0 && matrix[0].size() > 0)
            {
                bool fInLastRow = false;
                bool fInLastCol = false;
                int lastRow = matrix.size() - 1;
                int lastCol = matrix[0].size() - 1;

                for (int row = lastRow; row >= 0; row--)
                {
                    for (int col = lastCol; col >= 0; col--)
                    {
                        if (matrix[row][col] == 0)
                        {
                            if (row == lastRow)
                            {
                                fInLastRow = true;
                            }
                            if (col == lastCol)
                            {
                                fInLastCol = true;
                            }
                            if (col != lastCol && row != lastRow)
                            {
                                matrix[row][matrix[row].size() - 1] = 0;
                                matrix[matrix.size() - 1][col] = 0;
                            }
                        }
                    }
                }

                for (int col = 0; col < lastCol; col++)
                {
                    if (matrix[lastRow][col] == 0)
                    {
                        for (int row = 0; row < lastRow; row++)
                        {
                            matrix[row][col] = 0;
                        }
                    }
                }

                for (int row = 0; row < lastRow; row++)
                {
                    if (matrix[row][lastCol] == 0)
                    {
                        for (int col = 0; col < lastCol; col++)
                        {
                            matrix[row][col] = 0;
                        }
                    }
                }

                if (fInLastCol)
                {
                    for (int row = 0; row <= lastRow; row++)
                    {
                        matrix[row][lastCol] = 0;
                    }
                }
                if (fInLastRow)
                {
                    for (int col = 0; col <= lastCol; col++)
                    {
                        matrix[lastRow][col] = 0;
                    }
                }
            }
        }
    };

    void RunTests()
    {
        Solution s;
        vector<vector<int>> s1 = {
            { 0, 1 }
        };
        s.setZeroes(s1);

        vector<vector<int>> j1 = {
            { 0, 0, 0, 5 },
            { 4, 3, 1, 4 },
            { 0, 1, 1, 4 },
            { 1, 2, 1, 3 },
            { 0, 0, 1, 1 }
        };
        s.setZeroes(j1);
    }
}