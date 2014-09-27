#include "stdafx.h"

namespace ValidNumber
{
    class Solution
    {
    public:
        const char* SkipWhite(const char* s)
        {
            while (iswspace(*s))
            {
                s++;
            }
            return s;
        }
        const char* SkipDigits(const char* s)
        {
            while (isdigit(*s))
            {
                s++;
            }
            return s;
        }
        const char* SkipPosNeg(const char* s)
        {
            if (*s == '+' || *s == '-')
            {
                s++;
            }
            return s;
        }
        bool IsFloat(const char* s)
        {
            return (*s == '.');
        }
        bool IsExponent(const char* s)
        {
            return (*s == 'e');
        }
        bool isValidTail(const char* s)
        {
            bool fRequiresDigits = false;
            if (IsExponent(s))
            {
                s++;
                s = SkipPosNeg(s);
                fRequiresDigits = true;
            }

            const char* s2 = SkipDigits(s);
            if (s2 != s || !fRequiresDigits)
            {
                s = s2;
                s = SkipWhite(s);
                if (*s == '\0')
                {
                    return true;
                }
            }
            return false;
        }

        bool isNumber(const char *s)
        {
            bool isValid = false;
            if (s != nullptr)
            {
                s = SkipWhite(s);
                s = SkipPosNeg(s);
                const char* s2 = SkipDigits(s);
                
                // We've parsed a leading set of digits
                if (s2 != s)
                {
                    s = s2;
                    if (IsFloat(s2))
                    {
                        s++;
                        s = SkipDigits(s);
                    }
                    isValid = isValidTail(s);
                }
                else
                {
                    if (IsFloat(s))
                    {
                        s++;
                        const char* s3 = SkipDigits(s);
                        if (s3 != s)
                        {
                            s = s3;
                            isValid = isValidTail(s);
                        }
                    }
                }
            }
            return isValid;
        }
    };

    void RunTests()
    {
        Solution s;

        _ASSERT(s.isNumber(".1"));
        _ASSERT(s.isNumber("1.431352e7"));
        _ASSERT(s.isNumber(" 005047e+6"));
    }
}