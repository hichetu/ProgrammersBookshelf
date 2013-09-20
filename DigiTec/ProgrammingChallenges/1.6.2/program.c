#include <stdio.h>
#include <memory.h>

int fieldCount = 0;
char field[102][102] = {0};
int ProcessField();

int main()
{
    while(ProcessField())
    {
    }
    return 0;
}

int ProcessField()
{
    unsigned long rows;
    unsigned long columns;
    unsigned long rowIter;
    unsigned long colIter;

    fscanf(stdin, "%lu %lu\n", &rows, &columns);

    if (rows == 0 && columns == 0)
    {
        return 0;
    }

    fieldCount++;
    memset(field, 0, sizeof(field));
    for (rowIter = 0; rowIter < rows; rowIter++)
    {
        fgets(&field[rowIter+1][1], 102, stdin);
    }
    if (fieldCount > 1)
    {
        printf("\n");
    }
    printf("Field #%d:\n", fieldCount);
    for (rowIter = 1; rowIter <= rows; rowIter++)
    {
        for (colIter = 1; colIter <= columns; colIter++)
        {
            char type = field[rowIter][colIter];
            if (type == '*')
            {
                printf("*");
            }
            else
            {
                int bombs = (field[rowIter-1][colIter-1] == '*') +
                            (field[rowIter-1][colIter] == '*') +
                            (field[rowIter-1][colIter+1] == '*') +

                            (field[rowIter][colIter-1] == '*') +
                            (field[rowIter][colIter+1] == '*') +

                            (field[rowIter+1][colIter-1] == '*') +
                            (field[rowIter+1][colIter] == '*') +
                            (field[rowIter+1][colIter+1] == '*');
                printf("%d", bombs);
            }
        }
        printf("\n");
    }
    return 1;
}