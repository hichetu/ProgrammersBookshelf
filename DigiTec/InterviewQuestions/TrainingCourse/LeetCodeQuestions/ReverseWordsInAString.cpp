#include "stdafx.h"

namespace ReverseWordsInAString
{
    class Solution
    {
    public:
        void reverseWords(string &s)
        {
            while (s[0] == ' ')
            {
                s.erase(0, 1);
            }
            while (s.size() > 0 && s[s.size() - 1] == ' ')
            {
                s.erase(s.size() - 1, 1);
            }

            for (int i = s.size() - 2; i > 0; i--)
            {
                if (s[i] == ' ' && s[i] == s[i - 1])
                {
                    s.erase(i, 1);
                }
            }

            reverse(s, 0, s.size() - 1);
            int i = 0;
            int j = 0;
            for (; i < s.size() && j < s.size(); j++)
            {
                if (s[j] == ' ')
                {
                    reverse(s, i, j - 1);
                    i = j + 1;
                }
            }

            if (i < --j)
            {
                reverse(s, i, j);
            }
        }

        void reverse(string &s, int start, int end)
        {
            int i = start;
            int j = end;
            while (i < j)
            {
                char temp = s[i];
                s[i] = s[j];
                s[j] = temp;
                i++; j--;
            }
        }
    };

    void RunTests()
    {
        string empty = "";
        string emptySpace = "   ";
        string simple = "a";
        string original = "the sky is blue";

        Solution s;
        s.reverseWords(empty); _ASSERT(empty == "");
        s.reverseWords(emptySpace); _ASSERT(emptySpace == "");
        s.reverseWords(simple); _ASSERT(simple == "a");
        s.reverseWords(original); _ASSERT(original == "blue is sky the");
    }
}