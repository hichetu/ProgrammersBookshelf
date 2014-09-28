#include "stdafx.h"

namespace SubstringWithConcatOfAllWords
{
    class Solution
    {
    public:
        vector<int> findSubstring(string S, vector<string> &L)
        {
            unordered_map<string, int> dict;
            vector<int> indices;
            if (L.size() > 0)
            {
                int wordSize = L[0].size();
                int expectedSize = L.size() * wordSize;
                if (S.size() >= expectedSize)
                {
                    for (const string& s : L)
                    {
                        dict[s]++;
                    }

                    for (int i = 0; i <= S.size() - expectedSize; i++)
                    {
                        int matches = 0;
                        int offset = i;
                        while (matches < L.size())
                        {
                            string subStr = S.substr(offset, wordSize);
                            auto it = dict.find(subStr);
                            if (it != dict.end() && (*it).second > 0)
                            {
                                (*it).second--;
                                matches++;
                                offset += wordSize;
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (matches > 0)
                        {
                            dict.clear();
                            if (matches == L.size())
                            {
                                indices.push_back(i);
                            }
                            for (const string& s : L)
                            {
                                dict[s]++;
                            }
                        }
                    }
                }
            }
            return indices;
        }
    };

    void RunTests()
    {
        Solution s;

        string s1 = "barfoothefoobarman";
        vector<string> s1dict = { "bar", "foo" };
        vector<int> r1 = s.findSubstring(s1, s1dict);
        _ASSERT(r1.size() == 2);
        _ASSERT(r1[0] == 0);
        _ASSERT(r1[1] == 9);

        string j1 = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
        vector<string> j1dict = { "fooo", "barr", "wing", "ding", "wing" };
        vector<int> j1res = s.findSubstring(j1, j1dict);
        _ASSERT(j1res.size() == 1);
        _ASSERT(j1res[0] == 13);
    }
}