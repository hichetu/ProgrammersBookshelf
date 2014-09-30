#include "stdafx.h"

namespace PalindromePartitioning2
{
    class Solution
    {
    public:
        bool isPalindrome(string s)
        {
            auto itStart = s.begin();
            auto itEnd = s.end() - 1;

            while (itStart < itEnd)
            {
                if (*itStart++ != *itEnd--)
                {
                    return false;
                }
            }
            return true;
        }

        int minCut(string s)
        {
            map<int, int> idealCuts;
            int minCut = repartition(s, 0, idealCuts);
            return minCut;
        }

        int repartition(string s, int curCuts, map<int, int>& idealCuts)
        {
            if (isPalindrome(s))
            {
                return curCuts;
            }

            int minCuts = s.size() + curCuts;
            for (int i = s.size() - 1; i >= 1; i--)
            {
                string prefix = s.substr(0, i);
                if (isPalindrome(prefix))
                {
                    int offset = s.size() - i;
                    if (idealCuts.count(offset) == 0)
                    {
                        idealCuts[offset] = repartition(s.substr(i), curCuts + 1, idealCuts) - curCuts;
                    }
                    int partitionCuts = idealCuts[offset] + curCuts;
                    minCuts = min(minCuts, partitionCuts);
                    if (minCuts == (curCuts + 1))
                    {
                        break;
                    }
                }
            }
            return minCuts;
        }
    };

    void RunTests()
    {
        Solution s;
        string s1 = "aab";
        _ASSERT(s.minCut(s1) == 1);

        string s2 = "abcd";
        _ASSERT(s.minCut(s2) == 3);

        string s3 = "abba";
        _ASSERT(s.minCut(s3) == 0);

        string s4 = "abbaacca";
        _ASSERT(s.minCut(s4) == 1);

        string s5 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        _ASSERT(s.minCut(s5) == 1);
    }
}