#include <stdio.h>

void ProcessSet(unsigned long ulSetValues)
{
	unsigned long fValid = 1;
	unsigned long ulCurrentValue = 0;
	long lLastValue = 0;
	char* pSet = (char*) malloc(ulSetValues);
	memset(pSet, 0, ulSetValues);

	scanf("%ld", &lLastValue);
	for (ulCurrentValue = 1; ulCurrentValue < ulSetValues; ulCurrentValue++)
	{
		unsigned long ulDiff = 0;
		long lReadValue = 0;
		scanf("%ld", &lReadValue);

		if (lLastValue < lReadValue)
		{
			ulDiff = lReadValue - lLastValue;
		}
		else
		{
			ulDiff = lLastValue - lReadValue;
		}

		if (ulDiff == 0 || ulDiff >= ulSetValues || pSet[ulDiff] == 1)
		{
			fValid = 0;
		}
		else
		{
			pSet[ulDiff] = 1;
		}
		lLastValue = lReadValue;
	}

	if (fValid)
	{
		printf("Jolly\n");
	}
	else
	{
		printf("Not jolly\n");
	}

	free(pSet);
}

int main(int argc, char* argv)
{
	unsigned long ulSetCount = 0;
	while (scanf("%lu", &ulSetCount) != EOF)
	{
		ProcessSet(ulSetCount);
	}

	return 0;
}