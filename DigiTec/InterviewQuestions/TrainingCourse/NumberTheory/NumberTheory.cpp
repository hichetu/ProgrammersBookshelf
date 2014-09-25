// NumberTheory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

unsigned long divide(unsigned long x, unsigned long y)
{
    unsigned long dividend = 0;
    while (y <= x)
    {
        unsigned long current = y;
        unsigned long times = 1;
        while ((current << 1) < x)
        {
            current <<= 1;
            times <<= 1;
        }
        x -= current;
        dividend += times;
    }
    return dividend;
}

int _tmain(int argc, _TCHAR* argv[])
{
    assert(3 == divide(21, 7));
    assert(1 == divide(7, 5));
    return 0;
}

