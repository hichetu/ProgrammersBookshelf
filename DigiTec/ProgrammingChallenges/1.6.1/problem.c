#include <stdio.h>
#include <minmax.h>

int main()
{
    long sequenceStart;
    long sequenceEnd;

    while (scanf("%d %d", &sequenceStart, &sequenceEnd) != EOF)
    {
        long maxCycleLength = 0;
        long sequenceCur;
        for (sequenceCur = sequenceStart; sequenceCur <= sequenceEnd; sequenceCur++)
        {
            // If we start at 1 the value is 1
            long cycleLength = 1;
            long cur = sequenceCur;
            while (cur != 1)
            {
                cycleLength++;
                if (cur % 2 == 1)
                {
                    cur = 3*cur+1;
                }
                else
                {
                    cur = cur >> 1;
                }
            }

            maxCycleLength = max(cycleLength, maxCycleLength);
        }
        printf("%d %d %d\n", sequenceStart, sequenceEnd, maxCycleLength);
    }
}