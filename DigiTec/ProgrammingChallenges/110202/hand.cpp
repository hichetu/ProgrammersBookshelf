#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "hand.h"

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
