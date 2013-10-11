#include <stdio.h>
#include <memory.h>
#include "hand.h"

unsigned long CreateCard(char value, char suit)
{
#if DEBUG
    printf("%c %c\n", value, suit);
#endif
    unsigned long cardValue = 0;
    switch (value)
    {
        case '2': cardValue = 2; break;
        case '3': cardValue = 3; break;
        case '4': cardValue = 4; break;
        case '5': cardValue = 5; break;
        case '6': cardValue = 6; break;
        case '7': cardValue = 7; break;
        case '8': cardValue = 8; break;
        case '9': cardValue = 9; break;
        case 'T': cardValue = 10; break;
        case 'J': cardValue = 11; break;
        case 'Q': cardValue = 12; break;
        case 'K': cardValue = 13; break;
        case 'A': cardValue = 14; break;
    }

    switch (suit)
    {
        case 'H': cardValue += 1 << 4; break;
        case 'C': cardValue += 2 << 4; break;
        case 'D': cardValue += 3 << 4; break;
        case 'S': cardValue += 4 << 4; break;
    }
    return cardValue;
}

int main(int argc, char* argv)
{
    char card[20];

    while (scanf("%s", &card) != EOF)
    {
        unsigned long cards[5] = {0};
        cards[0] = CreateCard(card[0], card[1]);

        for (int i = 1; i < 5; i++)
        {
            scanf("%s", &card);
            cards[i] = CreateCard(card[0], card[1]);
        }

        CPokerHand blackHand(cards);
#if DEBUG
        blackHand.PrintHand();
#endif

        for (int i = 0; i < 5; i++)
        {
            scanf("%s", &card);
            cards[i] = CreateCard(card[0], card[1]);
        }

        CPokerHand whiteHand(cards);
#if DEBUG
        whiteHand.PrintHand();
#endif
        switch (blackHand.CompareHands(whiteHand))
        {
            case 1:
                printf("Black wins.\n");
                break;
            case 0:
                printf("Tie.\n");
                break;
            case -1:
                printf("White wins.\n");
                break;
        }
    }
}