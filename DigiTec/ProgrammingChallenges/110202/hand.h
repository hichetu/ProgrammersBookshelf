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
    CPokerHand(unsigned long* cards)
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