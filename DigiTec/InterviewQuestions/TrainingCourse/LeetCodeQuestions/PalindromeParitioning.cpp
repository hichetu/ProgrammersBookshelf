#include "stdafx.h"

namespace PalindromePartitioning
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

        vector<vector<string>> partition(string s)
        {
            vector<vector<string>> partitions;
            vector<string> parts;
            repartition(partitions, parts, s);
            return partitions;
        }

        bool repartition(vector<vector<string>>& partitions, vector<string>& parts, string sub)
        {
            if (sub.size() == 0)
            {
                return true;
            }
            for (int i = 0; i < sub.size(); i++)
            {
                string prefix = sub.substr(0, i + 1);
                if (isPalindrome(prefix))
                {
                    parts.push_back(prefix);
                    if (repartition(partitions, parts, sub.substr(i + 1)))
                    {
                        partitions.push_back(parts);
                    }
                    parts.pop_back();
                }
            }
            return false;
        }
    };

    void RunTests()
    {
        Solution s;
        string s1 = "aab";
        vector<vector<string>> r1 = s.partition(s1);
    }
}