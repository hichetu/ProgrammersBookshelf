#include <stdio.h>
#include <memory.h>
#include <math.h>

#define EPSILON 0.00000000001
int debugMode = 0;

void ProcessTrip(unsigned long students);
int main(int argc)
{
    unsigned long students;

    if (argc > 1)
    {
        printf("Debug Mode...\n");
        debugMode = 1;
    }

    fscanf(stdin, "%d\n", &students);
    while (students > 0)
    {
        ProcessTrip(students);
        fscanf(stdin, "%d\n", &students);
    }
    return 0;
}

double studentSpend[1000];
void ProcessTrip(unsigned long students)
{
    double amtTotal = 0;
    double amtAvg = 0;
    double negDiff = 0;
    double posDiff = 0;
    double acceptedDiff;

    unsigned long amtIter;
    for (amtIter = 0; amtIter < students; amtIter++)
    {
        fscanf(stdin, "%lf\n", &studentSpend[amtIter]);
        amtTotal += studentSpend[amtIter];
    }

    amtAvg = amtTotal / students;
    if (debugMode)
    {
        printf("Target Average: %lf\n", amtAvg);
    }
    for (amtIter = 0; amtIter < students; amtIter++)
    {
        // Trickiness here is casting to ensure roundness to "cents" in the numbers.
        // double diff = (double) (long) ((studentSpend[amtIter] - amtAvg) * 100) / 100;
        double diff = (double) (long) ((studentSpend[amtIter] - amtAvg) * 100 + EPSILON) / 100;

        if (debugMode)
        {
            printf("Computational Diff: %lf\n", studentSpend[amtIter] - amtAvg);
            printf("Computational Diff 2: %lf\n", (studentSpend[amtIter] - amtAvg) * 100);
            printf("Computational Diff 3: %lf\n", (studentSpend[amtIter] - amtAvg) * 100 / 100);
            printf("Computational Diff 4: %lu\n", (unsigned long) ((studentSpend[amtIter] - amtAvg) * 100));
        }

        if (diff > 0)
        {
            if (debugMode)
            {
                printf("Positive Diff: %lf for spend %lf\n", diff, studentSpend[amtIter]);
            }
            posDiff += diff;
        }
        else
        {
            if (debugMode)
            {
                printf("Negative Diff: %lf for spend %lf\n", diff, studentSpend[amtIter]);
            }
            negDiff += diff;
        }
    }

    if (debugMode)
    {
        printf("Diffs: neg($%.2lf), pos($%.2lf)\n", negDiff, posDiff);
    }

    acceptedDiff = posDiff;
    if (-negDiff > posDiff)
    {
        acceptedDiff = -negDiff;
    }
    printf("$%.2lf\n", acceptedDiff);
}