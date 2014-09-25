#include "stdafx.h"

namespace ValidPalindrome
{
    class Solution
    {
    public:
        bool isPalindrome(string s)
        {
            const char* pStart = s.c_str();
            const char* pEnd = pStart + s.size();

            do
            {
                while (pEnd > pStart)
                {
                    if (!isalnum(*pEnd))
                    {
                        pEnd--;
                    }
                    else
                    {
                        break;
                    }
                }
                while (pStart < pEnd)
                {
                    if (!isalnum(*pStart))
                    {
                        pStart++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (tolower(*pStart++) != tolower(*pEnd--))
                {
                    return false;
                }
            }
            while (pEnd > pStart);
            return true;
        }
    };
};