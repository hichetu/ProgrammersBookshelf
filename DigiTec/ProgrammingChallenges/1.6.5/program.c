#include <stdio.h>
#include <memory.h>

int debugMode = 0;
char bitmap[250][250];
unsigned long width;
unsigned long height;

void ClearImage();
char GetPixel(unsigned long x, unsigned long y);
void SetPixel(unsigned long x, unsigned long y, char color);
void DrawRectangle(unsigned long x1, unsigned long x2, unsigned long y1, unsigned long y2, char color);
void SaveBitmap(char* szFile);
void Fill(unsigned long x, unsigned long y, char color);
void SwapMax(unsigned long* ul1, unsigned long* ul2);

int main(int argc)
{
    if (argc > 1)
    {
        debugMode = 1;
    }

    do
    {
        char commandLine[1024];
        char* command = gets(commandLine);

        if (command == NULL)
        {
            break;
        }

        if (debugMode)
        {
            printf("Command %c\n", command[0]);
        }

        switch (command[0])
        {
            case 'I':
                sscanf(&command[1], "%d %d", &width, &height);
                if (debugMode)
                {
                    printf("I with %d %d\n", width, height);
                }
                ClearImage();
                break;

            case 'C':
                ClearImage();
                break;

            case 'L':
                {
                    unsigned long x;
                    unsigned long y;
                    char color;
                    sscanf(&command[1], "%d %d %c", &x, &y, &color);
                    if (debugMode)
                    {
                        printf("L with %d %d %c\n", x, y, color);
                    }
                    SetPixel(x, y, color);
                }
                break;

            case 'V':
                {
                    unsigned long x;
                    unsigned long y1;
                    unsigned long y2;
                    char color;
                    sscanf(&command[1], "%d %d %d %c", &x, &y1, &y2, &color);
                    SwapMax(&y1, &y2);
                    DrawRectangle(x, x, y1, y2, color);
                }
                break;

            case 'H':
                {
                    unsigned long x1;
                    unsigned long x2;
                    unsigned long y;
                    char color;
                    sscanf(&command[1], "%d %d %d %c", &x1, &x2, &y, &color);
                    SwapMax(&x1, &x2);
                    DrawRectangle(x1, x2, y, y, color);
                }
                break;

            case 'K':
                {
                    unsigned long x1;
                    unsigned long x2;
                    unsigned long y1;
                    unsigned long y2;
                    char color;
                    sscanf(&command[1], "%d %d %d %d %c", &x1, &y1, &x2, &y2, &color);
                    SwapMax(&x1, &x2);
                    SwapMax(&y1, &y2);
                    DrawRectangle(x1, x2, y1, y2, color);
                }
                break;

            case 'F':
                {
                    unsigned long x;
                    unsigned long y;
                    char color;
                    sscanf(&command[1], "%d %d %c", &x, &y, &color);
                    Fill(x, y, color);
                }
                break;

            case 'S':
                {
                    char achFile[1024];
                    sscanf(&command[1], "%s", &achFile);
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
    char colorSrc = GetPixel(x, y);

    // If we fill the same color, then that would be a no-op
    if (colorSrc != color)
    {
        SetPixel(x, y, color);
        if (ComparePixel(x, y-1, colorSrc))
        {
            Fill(x, y-1, color);
        }
        if (ComparePixel(x, y+1, colorSrc))
        {
            Fill(x, y+1, color);
        }
        if (ComparePixel(x-1, y, colorSrc))
        {
            Fill(x-1, y, color);
        }
        if (ComparePixel(x+1, y, colorSrc))
        {
            Fill(x+1, y, color);
        }
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
