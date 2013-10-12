#include <stdio.h>

// This problem can be solved by counting the values in a set. To implement a fast set
// I'll be using a bit-field that determines if that day is set or not. When setting a
// new value in place I'll utilize a counter. This will mean once I've completed my
// pass through for each party, I'll already have the count of days lost.

void ThrowOnBadRange(unsigned long ulValue, unsigned long ulMin, unsigned long ulMax)
{
    if (ulValue < ulMin || ulValue > ulMax)
    {
        int* p = 0;
        (*p) = 1;
    }
}

void HangOnBadRead()
{
    while(1)
    {
    }
}

int main(int argc, char* argv)
{
    unsigned long ulTestCases = 0;
    if (scanf("%lu", &ulTestCases) != EOF)
    {
        unsigned long ulTestCase = 0;
        for (;ulTestCase < ulTestCases; ulTestCase++)
        {
            unsigned long ulSimulationDays = 0;
            if (scanf("%lu", &ulSimulationDays))
            {
                unsigned long ulParties = 0;
                ThrowOnBadRange(ulSimulationDays, 7, 3650);
                if (scanf("%lu", &ulParties))
                {
                    ThrowOnBadRange(ulParties, 1, 100);
                    {
                        unsigned long ulStrikeDays = 0;
                        unsigned long ulParty = 0;
                        unsigned long ulBuckets = ulSimulationDays + 7 / 8;
                        char* bitBucket = (char*) malloc(ulBuckets);
                        memset(bitBucket, 0, ulBuckets);

                        for (;ulParty < ulParties; ulParty++)
                        {
                            unsigned long ulParmHartal = 0;
                            if (scanf("%lu", &ulParmHartal))
                            {
                                // Assume we are 0 indexed for the first Sunday
                                unsigned long ulHartalDay = ulParmHartal - 1;
                                while (ulHartalDay < ulSimulationDays)
                                {
                                    // Gracefully skip Friday and Saturday, because we are 0 indexed fri/sat are 5 and 6 respectively.
                                    if (ulHartalDay % 7 != 5 && ulHartalDay % 7 != 6)
                                    {
                                        // Figure out the location in our set.
                                        unsigned long bucket = ulHartalDay / 8;
                                        unsigned long bit = ulHartalDay % 8;
                                        unsigned long bucketValue = bitBucket[bucket];

                                        if ((bucketValue & (1 << bit)) == 0)
                                        {
                                            bitBucket[bucket] = bucketValue | (1 << bit);
                                            ulStrikeDays++;
                                        }
                                    }
                                    ulHartalDay += ulParmHartal;
                                }
                            }
                            else
                            {
                                HangOnBadRead();
                            }
                        }

                        printf("%d\n", ulStrikeDays);
                    }
                }
                else
                {
                    HangOnBadRead();
                }
            }
            else
            {
                HangOnBadRead();
            }
        }
    }
    return 0;
}