#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#pragma once

enum HAND_TYPE
{
    HAND_TYPE_NONE          = 0x0,
    HAND_TYPE_HIGHCARDMASK  = 0xF,
    HAND_TYPE_NEXTCARDMASK  = 0xF0,
    HAND_TYPE_PAIR          = 0x100,
    HAND_TYPE_TWOPAIR       = 0x200,
    HAND_TYPE_COMPARE_MASK  = 0x3FF,
    HAND_TYPE_THREE         = 0x400,
    HAND_TYPE_STRAIGHT      = 0x800,
    HAND_TYPE_FLUSH         = 0x1000,
    HAND_TYPE_FULLHOUSE     = 0x2000,
    HAND_TYPE_FOUR          = 0x4000,
    HAND_TYPE_STRAIGHT_FLUSH= 0x8000,
};

class CPokerHand
{
public:
    CPokerHand(unsigned long cards[5])
    {
        memcpy(m_cards, cards, sizeof(unsigned long) * 5);
    }

    int CompareHands(CPokerHand& other);
    void PrintHand();

private:
    unsigned long ComputeHandValue();

    bool IsFlush();
    bool IsStraight();
    unsigned long ComputeOfAKindValue();
    unsigned long HighCard();
    static int CompareCards(const void* arg1, const void* arg2);

    unsigned long m_cards[5];
};

void CPokerHand::PrintHand()
{
    for (int i = 0; i < 5; i++)
    {
        printf("value %d suit %d ", m_cards[i] & 0xF, (m_cards[i] & ~0xF) >> 4);
    }
    printf("\n");
}

int CPokerHand::CompareHands(CPokerHand& other)
{
    unsigned long myHandValue = ComputeHandValue();
    unsigned long otherHandValue = other.ComputeHandValue();

    if (myHandValue > otherHandValue)
    {
        return 1;
    }
    else if (myHandValue < otherHandValue)
    {
        return -1;
    }
    else
    {
        qsort(m_cards, 5, sizeof(unsigned long), &CPokerHand::CompareCards);
        qsort(other.m_cards, 5, sizeof(unsigned long), &CPokerHand::CompareCards);

        for (int i = 4; i >= 0; i--)
        {
            if ((m_cards[i] & 0xF) > (other.m_cards[i] & 0xF))
            {
                return 1;
            }
            else if ((m_cards[i] & 0xF) < (other.m_cards[i] & 0xF))
            {
                return -1;
            }
        }
    }

    return 0;
}

unsigned long CPokerHand::ComputeHandValue()
{
    bool fIsStraight = IsStraight();
    bool fIsFlush = IsFlush();

    if (fIsStraight && fIsFlush)
    {
        return HighCard() | HAND_TYPE_STRAIGHT_FLUSH;
    }
    else if (fIsStraight)
    {
        return HighCard() | HAND_TYPE_STRAIGHT;
    }
    else if (fIsFlush)
    {
        return HighCard() | HAND_TYPE_FLUSH;
    }

    return ComputeOfAKindValue();
}

unsigned long CPokerHand::ComputeOfAKindValue()
{
    qsort(m_cards, 5, sizeof(unsigned long), CPokerHand::CompareCards);

    if ((m_cards[0] & 0xF) == (m_cards[3] & 0xF) || (m_cards[1] & 0xF) == (m_cards[4] & 0xF))
    {
        return HAND_TYPE_FOUR | (m_cards[1] & 0xF);
    }

    if ((m_cards[0] & 0xF) == (m_cards[2] & 0xF))
    {
        if ((m_cards[3] & 0xF) == (m_cards[4] & 0xF))
        {
            return HAND_TYPE_FULLHOUSE | (m_cards[2] & 0xF);
        }
        else
        {
            return HAND_TYPE_THREE | (m_cards[2] & 0xF);
        }
    }
    else if ((m_cards[1] & 0xF) == (m_cards[3] & 0xF))
    {
        return HAND_TYPE_THREE | (m_cards[2] & 0xF);
    }
    else if ((m_cards[2] & 0xF) == (m_cards[4] & 0xF))
    {
        if ((m_cards[0] & 0xF) == (m_cards[1] & 0xF))
        {
            return HAND_TYPE_FULLHOUSE | (m_cards[2] & 0xF);
        }
        else
        {
            return HAND_TYPE_THREE | (m_cards[2] & 0xF);
        }
    }

    unsigned long pair1 = ((m_cards[0] & 0xF) == (m_cards[1] & 0xF)) ? (m_cards[0] & 0xF) : 0;
    unsigned long pair2 = ((m_cards[1] & 0xF) == (m_cards[2] & 0xF)) ? (m_cards[1] & 0xF) : 0;
    unsigned long pair3 = ((m_cards[2] & 0xF) == (m_cards[3] & 0xF)) ? (m_cards[2] & 0xF) : 0;
    unsigned long pair4 = ((m_cards[3] & 0xF) == (m_cards[4] & 0xF)) ? (m_cards[3] & 0xF) : 0;

    unsigned long pairs[2] = {0};
    unsigned long pairCount = 0;
    if (pair1 > 0)
    {
        pairs[pairCount++] = pair1;
    }
    if (pair2 > 0)
    {
        pairs[pairCount++] = pair2;
    }
    if (pair3 > 0)
    {
        pairs[pairCount++] = pair3;
    }
    if (pair4 > 0)
    {
        pairs[pairCount++] = pair4;
    }

    if (pairCount == 2)
    {
        if (pairs[0] > pairs[1])
        {
            return (pairs[0] << 4 | pairs[1]) | HAND_TYPE_TWOPAIR;
        }
        else
        {
            return (pairs[1] << 4 | pairs[0]) | HAND_TYPE_TWOPAIR;
        }
    }
    else if (pairCount == 1)
    {
        return pairs[0] | HAND_TYPE_PAIR;
    }
    return HighCard();
}

unsigned long CPokerHand::HighCard()
{
    qsort(m_cards, 5, sizeof(unsigned long), CPokerHand::CompareCards);
    return (m_cards[4] & 0xF);

}

bool CPokerHand::IsStraight()
{
    bool fIsStraight = true;
    qsort(m_cards, 5, sizeof(unsigned long), CPokerHand::CompareCards);
    for (int i = 1; i < 5; i++)
    {
        if (m_cards[i - 1] != (m_cards[i] - 1))
        {
            fIsStraight = false;
            break;
        }
    }
    return fIsStraight;
}

bool CPokerHand::IsFlush()
{
    bool fIsFlush = true;
    for (int i = 1; i < 5; i++)
    {
        if ((m_cards[i - 1] & ~0xF) != (m_cards[i] & ~0xF))
        {
            fIsFlush = false;
            break;
        }
    }
    return fIsFlush;
}

int CPokerHand::CompareCards(const void* arg1, const void* arg2)
{
    long left = (*(long*)arg1) & 0xF;
    long right = (*(long*)arg2) & 0xF;
    return left - right;
}

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