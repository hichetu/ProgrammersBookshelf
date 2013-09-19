#include <stdio.h>

// Fast method using precomputed memoization
long cycleLengths[1000001] = {0};
unsigned long cycleLength(long lStart)
{
    unsigned long cycleLength = 0;
    unsigned long lCur = lStart;

    for (;;)
    {
        if (lCur&1)
        {
            // This reduces more half of our loops. We know that if we multiply any 2 odd
            // numbers they become odd and then we add 1 so they become event. They are also
            // large so we immediately shift right. We add 2 for this.
            cycleLength+=2;
            lCur = (3*lCur+1) >> 1;
        }
        else
        {
            cycleLength++;
            lCur = lCur >> 1;
        }

        if (lCur < lStart)
        {
            break;
        }
    }
    return cycleLength + cycleLengths[lCur];
}

// Slower method
unsigned long cycleLengthSlow(long lStart)
{
    unsigned long cycleLength = 1;
    unsigned long lCur = lStart;
    while (lCur != 1)
    {
        if ((lCur%2)==1)
        {
            lCur = 3*lCur+1;
        }
        else
        {
            lCur = lCur / 2;
        }
        cycleLength++;
    }
    return cycleLength;
}

int main()
{
    unsigned long sequenceStart;
    unsigned long sequenceEnd;
    unsigned long initOffset;

    cycleLengths[1] = 1;
    for (initOffset = 2; initOffset <= 1000000; initOffset++)
    {
        if (initOffset % 2 == 0)
        {
            cycleLengths[initOffset] = 1 + cycleLengths[initOffset >> 1];
        }
        else
        {
            cycleLengths[initOffset] = cycleLength(initOffset);
        }

        /* Validation for the faster method by comparing against the slow method.
        if (cycleLengths[initOffset] != cycleLengthSlow(initOffset))
        {
            __debugbreak();
        }
        */
    }

    // Interestingly the %lu here and maybe in the printf are critical to passing the grader.
    // I wouldn't expect that to be the case, but I made about 15 submissions that were correct
    // but wouldn't pass because the output was wrong. Correcting these format strings fixed that.
    while (scanf("%lu %lu", &sequenceStart, &sequenceEnd) != EOF)
    {
        unsigned long maxCycleLength = 0;
        unsigned long sequenceCur;
        unsigned long sequenceIterStart = sequenceStart;
        unsigned long sequenceIterEnd = sequenceEnd;

        // They give input out of order so you have to flip it, but you still need to output
        // in the order you read in.
        if (sequenceStart > sequenceEnd)
        {
            sequenceIterStart = sequenceEnd;
            sequenceIterEnd = sequenceStart;
        }

        for (sequenceCur = sequenceIterStart; sequenceCur <= sequenceIterEnd; sequenceCur++)
        {
            unsigned long curCycleLength = cycleLengths[sequenceCur];
            if (curCycleLength > maxCycleLength)
            {
                maxCycleLength = curCycleLength;
            }
        }
        printf("%lu %lu %lu\n", sequenceStart, sequenceEnd, maxCycleLength);
    }
    return 0;
}