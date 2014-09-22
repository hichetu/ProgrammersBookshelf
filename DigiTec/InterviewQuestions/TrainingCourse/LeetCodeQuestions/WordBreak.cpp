#include "stdafx.h"

namespace WordBreak
{
    class Solution
    {
    public:
        bool wordBreak(string s, unordered_set<string> &dict)
        {
            map<int, bool> restMap;
            return subBreak(s, dict, restMap);
        }

        bool subBreak(string s, unordered_set<string> &dict, map<int, bool>& restMap)
        {
            for (int i = 1; i <= s.length(); i++)
            {
                string prefix = s.substr(0, i);
                if (dict.count(prefix) > 0)
                {
                    if (i < s.length())
                    {
                        string rest = s.substr(i);
                        auto it = restMap.find(rest.length());
                        if (it == restMap.end())
                        {
                            restMap[rest.length()] = subBreak(rest, dict, restMap);
                        }
                        
                        if (restMap[rest.length()])
                        {
                            return true;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    };

    void RunTests()
    {
        Solution s;
        string test1 = "leetcode";
        unordered_set<string> testdict1{ "leet", "code" };
        _ASSERT(s.wordBreak(test1, testdict1));

        string judgeTest1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
        unordered_set<string> judgedict1{ "a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa" };
        _ASSERT(!s.wordBreak(judgeTest1, judgedict1));
    }
}