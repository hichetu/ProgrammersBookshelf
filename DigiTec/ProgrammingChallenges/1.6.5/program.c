#include <stdio.h>
#include <memory.h>

char bitmap[250][250];
unsigned long width;
unsigned long height;

void ClearImage();
char GetPixel(unsigned long x, unsigned long y);
void SetPixel(unsigned long x, unsigned long y, char color);
void DrawRectangle(unsigned long x1, unsigned long x2, unsigned long y1, unsigned long y2, char color);
void SaveBitmap(char* szFile);
void Fill(unsigned long x, unsigned long y, char color);
void FillWorker(unsigned long x, unsigned long y, char color, char oldColor);
void SwapMax(unsigned long* ul1, unsigned long* ul2);

int main(int argc)
{
    do
    {
        char targetCommand;
        char commandLine[1024];
        char* command = gets(commandLine);

        if (command == NULL)
        {
            break;
        }

        sscanf(command, "%c", &targetCommand);
        switch (targetCommand)
        {
            case 'I':
                sscanf(&command[1], "%c %lu %lu", &targetCommand, &width, &height);
                ClearImage();
                break;

            case 'C':
                ClearImage();
                break;

            case 'L':
                {
                    unsigned long x = 0;
                    unsigned long y = 0;
                    char color = 0;
                    sscanf(&command[1], "%c %lu %lu %c", &targetCommand, &x, &y, &color);
                    SetPixel(x, y, color);
                }
                break;

            case 'V':
                {
                    unsigned long x = 0;
                    unsigned long y1 = 0;
                    unsigned long y2 = 0;
                    char color = 0;
                    sscanf(&command[1], "%c %lu %lu %lu %c", &targetCommand, &x, &y1, &y2, &color);
                    SwapMax(&y1, &y2);
                    DrawRectangle(x, x, y1, y2, color);
                }
                break;

            case 'H':
                {
                    unsigned long x1 = 0;
                    unsigned long x2 = 0;
                    unsigned long y = 0;
                    char color = 0;
                    sscanf(&command[1], "%c %lu %lu %lu %c", &targetCommand, &x1, &x2, &y, &color);
                    SwapMax(&x1, &x2);
                    DrawRectangle(x1, x2, y, y, color);
                }
                break;

            case 'K':
                {
                    unsigned long x1 = 0;
                    unsigned long x2 = 0;
                    unsigned long y1 = 0;
                    unsigned long y2 = 0;
                    char color = 0;
                    sscanf(&command[1], "%c %lu %lu %lu %lu %c", &targetCommand, &x1, &y1, &x2, &y2, &color);
                    SwapMax(&x1, &x2);
                    SwapMax(&y1, &y2);
                    DrawRectangle(x1, x2, y1, y2, color);
                }
                break;

            case 'F':
                {
                    unsigned long x = 0;
                    unsigned long y = 0;
                    char color = 0;
                    sscanf(&command[1], "%c %lu %lu %c", &targetCommand, &x, &y, &color);
                    Fill(x, y, color);
                }
                break;

            case 'S':
                {
                    char achFile[1024];
                    sscanf(&command[1], "%c %s", &targetCommand, &achFile);
                    SaveBitmap(achFile);
                }
                break;

            case 'X':
                return 0;

            default:
                break;
        }
    }
    while (1);

    return 0;
}

void ClearImage()
{
    memset(bitmap, 'O', sizeof(bitmap));
}

void SetPixel(unsigned long x, unsigned long y, char color)
{
    bitmap[y-1][x-1] = color;
}

int ComparePixel(unsigned long x, unsigned long y, char color)
{
    if (x < 1 || x > width || y < 1 || y > height)
    {
        return 0;
    }
    else
    {
        return (GetPixel(x, y) == color) ? 1 : 0;
    }
}

char GetPixel(unsigned long x, unsigned long y)
{
    if (x < 1 || x > width || y < 1 || y > height)
    {
        return 0xFF;
    }
    else
    {
        return bitmap[y-1][x-1];
    }
}

void DrawRectangle(unsigned long x1, unsigned long x2, unsigned long y1, unsigned long y2, char color)
{
    unsigned long xOffset;
    unsigned long yOffset;

    for (yOffset = y1; yOffset <= y2; yOffset++)
    {
        for (xOffset = x1; xOffset <= x2; xOffset++)
        {
            SetPixel(xOffset, yOffset, color);
        }
    }
}

void SaveBitmap(char* szFile)
{
    unsigned long xOffset;
    unsigned long yOffset;

    printf("%s\n", szFile);

    for (yOffset = 0; yOffset < height; yOffset++)
    {
        for (xOffset = 0; xOffset < width; xOffset++)
        {
            printf("%c", bitmap[yOffset][xOffset]);
        }
        printf("\n");
    }
}

void Fill(unsigned long x, unsigned long y, char color)
{
    char oldColor = GetPixel(x, y);

    // If we fill the same color, then that would be a no-op
    if (oldColor != color)
    {
        FillWorker(x, y, color, oldColor);
    }
}

void FillWorker(unsigned long x, unsigned long y, char color, char oldColor)
{
    SetPixel(x, y, color);
    if (ComparePixel(x, y-1, oldColor))
    {
        FillWorker(x, y-1, color, oldColor);
    }
    if (ComparePixel(x, y+1, oldColor))
    {
        FillWorker(x, y+1, color, oldColor);
    }
    if (ComparePixel(x-1, y, oldColor))
    {
        FillWorker(x-1, y, color, oldColor);
    }
    if (ComparePixel(x+1, y, oldColor))
    {
        FillWorker(x+1, y, color, oldColor);
    }
}


void SwapMax(unsigned long* ul1, unsigned long* ul2)
{
    if (*ul1 > *ul2)
    {
        unsigned long ulTmp = *ul1;
        *ul1 = *ul2;
        *ul2 = ulTmp;
    }
}
