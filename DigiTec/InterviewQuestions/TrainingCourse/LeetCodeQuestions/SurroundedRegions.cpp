#include "stdafx.h"

namespace SurroundedRegions
{
    class Solution
    {
    public:
        void solve(vector<vector<char>> &board)
        {
            if (board.size() > 2)
            {
                vector<pair<int, int>> graph;

                int width = board[0].size();
                int height = board.size();

                map<pair<int, int>, bool> seen;

                // Process the left and right edges
                for (int i = 0; i < height; i++)
                {
                    if (board[i][0] == 'O')
                    {
                        graph.push_back({ i, 0 });
                        seen[graph.back()] = true;
                    }
                    if (board[i][width - 1] == 'O')
                    {
                        graph.push_back({ i, width - 1 });
                        seen[graph.back()] = true;
                    }
                }
                // Process the top and bottom edges
                for (int i = 1; i < width - 1; i++)
                {
                    if (board[0][i] == 'O')
                    {
                        graph.push_back({ 0, i });
                        seen[graph.back()] = true;
                    }
                    if (board[height - 1][i] == 'O')
                    {
                        graph.push_back({ height - 1, i });
                        seen[graph.back()] = true;
                    }
                }

                while (!graph.empty())
                {
                    pair<int, int> currentPair = graph.back();
                    graph.pop_back();
                    seen[currentPair] = true;

                    board[currentPair.first][currentPair.second] = '+';

                    pair<int, int> fourSquare[4] = {
                        { currentPair.first, currentPair.second - 1},
                        { currentPair.first, currentPair.second + 1 },
                        { currentPair.first + 1, currentPair.second },
                        { currentPair.first - 1, currentPair.second }
                    };
                    for (int i = 0; i < _countof(fourSquare); i++)
                    {
                        pair<int, int> newPair = fourSquare[i];
                        if (seen.count(newPair) == 0)
                        {
                            if (newPair.first > 0 && newPair.first < height && newPair.second > 0 && newPair.second < width)
                            {
                                if (board[newPair.first][newPair.second] == 'O')
                                {
                                    graph.push_back(newPair);
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i < board.size(); i++)
                {
                    for (int j = 0; j < board[i].size(); j++)
                    {
                        if (board[i][j] == '+')
                        {
                            board[i][j] = 'O';
                        }
                        else
                        {
                            board[i][j] = 'X';
                        }
                    }
                }
            }
        }
    };

    void PrintResults(vector<vector<char>>& board)
    {
        for (const vector<char>& row : board)
        {
            for (const char& col : row)
            {
                printf("%c ", col);
            }
            printf("\n");
        }
    }

    void RunTests()
    {
        Solution s;
        vector<vector<char>> s1 = {
            { 'X', 'X', 'X', 'X' },
            { 'X', 'O', 'O', 'X' },
            { 'X', 'X', 'O', 'X' },
            { 'X', 'O', 'X', 'X' }
        };
        s.solve(s1);
        PrintResults(s1);

        vector<vector<char>> s2 = {
            { 'O', 'O', 'O', 'O', 'X', 'X' },
            { 'O', 'O', 'O', 'O', 'O', 'O' },
            { 'O', 'X', 'O', 'X', 'O', 'O' },
            { 'O', 'X', 'O', 'O', 'X', 'O' },
            { 'O', 'X', 'O', 'X', 'O', 'O' },
            { 'O', 'X', 'O', 'O', 'O', 'O' }
        };
        s.solve(s2);
        PrintResults(s2);

        vector<vector<char>> s3 = {
            { 'O', 'X', 'X', 'O', 'X' },
            { 'X', 'O', 'O', 'X', 'O' },
            { 'X', 'O', 'X', 'O', 'X' },
            { 'O', 'X', 'O', 'O', 'O' },
            { 'X', 'X', 'O', 'X', 'O' }
        };
        s.solve(s3);
        PrintResults(s3);
        getchar();
    }
}