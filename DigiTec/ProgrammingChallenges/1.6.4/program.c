#include <stdio.h>
#include <math.h>

unsigned long aryDigits[10];
unsigned long digits;
void ComputeDigits(unsigned long value);
void PrintLed(unsigned long spacing, unsigned long value);
void PrintChars(unsigned long spacing, char symbol);
int main()
{
    unsigned long spacing;
    unsigned long value;
    fscanf(stdin, "%lu %lu\n", &spacing, &value);

    while (spacing > 0)
    {
        ComputeDigits(value);
        PrintLed(spacing, value);
        fscanf(stdin, "%d %d\n", &spacing, &value);
    }
    return 0;
}

// Each letter has 7 regions across 5 lines.
char drawProgram[] =
{
    // 0
    '-', '|', '|', ' ', '|', '|', '-',
    // 1
    ' ', ' ', '|', ' ', ' ', '|', ' ',
    // 2
    '-', ' ', '|', '-', '|', ' ', '-',
    // 3
    '-', ' ', '|', '-', ' ', '|', '-',
    // 4
    ' ', '|', '|', '-', ' ', '|', ' ',

    // 5
    '-', '|', ' ', '-', ' ', '|', '-',
    // 6
    '-', '|', ' ', '-', '|', '|', '-',
    // 7
    '-', ' ', '|', ' ', ' ', '|', ' ',
    // 8
    '-', '|', '|', '-', '|', '|', '-',
    // 9
    '-', '|', '|', '-', ' ', '|', '-',
};

void ComputeDigits(unsigned long value)
{
    // This was a special case value. I improved the input to contain a line with:
    //    1 0
    if (value == 0)
    {
        digits = 1;
        aryDigits[0] = 0;
    }
    else
    {
        unsigned long digitIter;
        digits = (int) (log10((double) value) + 1);

        for (digitIter = digits; digitIter > 0; digitIter--)
        {
            aryDigits[digitIter - 1] = (value % 10);
            value /= 10;
        }
    }
}

void PrintLed(unsigned long spacing, unsigned long value)
{
    unsigned long drawLine = 0;

    while (drawLine < 5)
    {
        unsigned long digitIter;
        unsigned long barIter;
        unsigned long barIterations = 1;
        switch (drawLine)
        {
            case 1:
            case 3:
                barIterations = spacing;
                break;
        }

        for (barIter = 0; barIter < barIterations; barIter++)
        {
            for (digitIter = 0; digitIter < digits; digitIter++)
            {
                unsigned long digit = aryDigits[digitIter];
                switch (drawLine)
                {
                    case 0:
                        printf(" ");
                        PrintChars(spacing, drawProgram[digit*7]);
                        printf(" ");
                        break;
                    case 1:
                        printf("%c", drawProgram[digit*7+1]);
                        PrintChars(spacing, ' ');
                        printf("%c", drawProgram[digit*7+2]);
                        break;
                    case 2:
                        printf(" ");
                        PrintChars(spacing, drawProgram[digit*7+3]);
                        printf(" ");
                        break;
                    case 3:
                        printf("%c", drawProgram[digit*7+4]);
                        PrintChars(spacing, ' ');
                        printf("%c", drawProgram[digit*7+5]);
                        break;
                    case 4:
                        printf(" ");
                        PrintChars(spacing, drawProgram[digit*7+6]);
                        printf(" ");
                        break;
                }
                if (digitIter < (digits - 1))
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        drawLine++;
    }
    printf("\n");
}

void PrintChars(unsigned long spacing, char symbol)
{
    while (spacing > 0)
    {
        printf("%c", symbol);
        spacing--;
    }
}