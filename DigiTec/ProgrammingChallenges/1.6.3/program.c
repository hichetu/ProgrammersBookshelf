#include <stdio.h>
#include <memory.h>

void ProcessTrip(unsigned long students);
int main()
{
    unsigned long students;
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

    unsigned long amtIter;
    for (amtIter = 0; amtIter < students; amtIter++)
    {
        fscanf(stdin, "%lf\n", &studentSpend[amtIter]);
        amtTotal += studentSpend[amtIter];
    }

    amtAvg = amtTotal / students;
    for (amtIter = 0; amtIter < students; amtIter++)
    {
        // Trickiness here is casting to ensure roundness to "cents" in the numbers.
        double diff = (double) (long) ((studentSpend[amtIter] - amtAvg) * 100) / 100;
        if (diff > 0)
        {
            posDiff += diff;
        }
        else
        {
            negDiff += diff;
        }
    }
    printf("$%.2lf\n", (-negDiff > posDiff) ? -negDiff : posDiff);
}