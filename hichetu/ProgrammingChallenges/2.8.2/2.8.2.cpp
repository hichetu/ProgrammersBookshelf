// 2.8.2.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110202

#include <bitset>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

enum Winner
{
	Black,
	White,
	None
};

enum Suit
{
	Clubs,
	Diamonds,
	Hearts,
	Spades,
};

class Card
{
public:
	Card(size_t value = 0, ::Suit suit = Clubs) : value_(value), suit_(suit) {}

	size_t& Value()
	{
		return value_;
	}

	::Suit& Suit()
	{
		return suit_;
	}

	bool operator<(const Card& card) const
	{
		return value_ < card.value_;
	}

private:
	size_t value_;
	::Suit suit_;
};

std::istream & operator>> (std::istream &in, Card& card)
{
	char vCh = 0;
	char sCh = 0;

	in >> vCh;
	in >> sCh;

	size_t value = 0;
	Suit suit = Clubs;

	switch(vCh)
	{
	case '2':
		value = 2;
		break;
	case '3':
		value = 3;
		break;
	case '4':
		value = 4;
		break;
	case '5':
		value = 5;
		break;
	case '6':
		value = 6;
		break;
	case '7':
		value = 7;
		break;
	case '8':
		value = 8;
		break;
	case '9':
		value = 9;
		break;
	case 'T':
		value = 10;
		break;
	case 'J':
		value = 11;
		break;
	case 'Q':
		value = 12;
		break;
	case 'K':
		value = 13;
		break;
	case 'A':
		value = 14;
		break;

	default:
		throw string("Input vCh Error");
		break;
	}

	switch(sCh)
	{
	case 'C':
		suit = Clubs;
		break;
	case 'H':
		suit = Hearts;
		break;
	case 'D':
		suit = Diamonds;
		break;
	case 'S':
		suit = Spades;
		break;

	default:
		throw string("Input sCh Error");
		break;
	}

	card.Value() = value;
	card.Suit() = suit;
}

class Poker
{

};

class PokerHands
{
public:
	void Solve()
	{
		while(ReadInput())
		{
			WhoWon();
			PrintWhoWon();
		}
	}

private:

	bool ReadInput()
	{
		input_.clear();

		getline(cin,input_);

		if(cin.bad())
		{
			return false;
		}

		if(input_.empty())
		{
			return false;
		}

		return true;
	}

	void WhoWon()
	{
		ReadBlackCards();
		ReadWhiteCards();
		PlayPoker();
		WhoWinsPoker();		
	}

	void WhoWinsPoker()
	{
		if(BlackWins())
		{
			output_ = "Black wins.";
		}
		else if(WhiteWins())
		{
			output_ = "White wins.";
		}
		else
		{
			output_ = "Tie.";
		}
	}

	void PlayPoker()
	{
		winner_ = None;

		if(CheckStraightFlush())
		{
			return;
		}

		if(CheckFourOfAKind())
		{
			return;
		}

		if(CheckFullHouse())
		{
			return;
		}

		if(CheckFlush())
		{
			return;
		}

		if(CheckStraight())
		{
			return;
		}

		if(CheckThreeOfAKind())
		{
			return;
		}

		if(CheckTwoPairs())
		{
			return;
		}

		if(CheckPair())
		{
			return;
		}

		if(CheckHighCard())
		{
			return;
		}
	}

	bool BlackWins() const
	{
		return winner_ == Black;
	}

	bool WhiteWins() const
	{
		return winner_ == White;
	}

	void ReadBlackCards()
	{
		stringstream stream(input_);

		for(size_t i=0; i<5; ++i)
		{
			stream >> blackCards[i];
		}
	}

	void ReadWhiteCards()
	{
		stringstream stream(input_);

		for(size_t i=0; i<5; ++i)
		{
			stream >> whiteCards[i];
		}
	}

	bool CheckStraightFlush()
	{


		return false;
	}

private:
	string input_;
	string output_;
	Winner winner_;
	Card blackCards[5];
	Card whiteCards[5];
};

int main()
{
	PokerHands problem;

	problem.Solve();

	return 0;
}