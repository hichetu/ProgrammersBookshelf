// 2.8.2.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110202

#include <bitset>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <functional>
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

	return in;
}

class PokerHand
{
public:

	void ReadInput(stringstream& data)
	{
		for(size_t i=0; i<5; ++i)
		{
			data >> cards_[i];
		}

		std::sort(cards_, cards_ + 5);
	}

	bool TryStraightFlush(vector<int>& rank)
	{
		rank.clear();

		bool isStraightFlush = true;
		Suit suit = cards_[0].Suit();
		int sValue = cards_[0].Value();

		for(size_t i=1; i<5; ++i)
		{
			if(cards_[i].Suit() != suit)
			{
				isStraightFlush = false;
				break;
			}

			if(cards_[i].Value() != ++sValue)
			{
				isStraightFlush = false;
				break;
			}
		}

		if(isStraightFlush)
		{
			rank.push_back(cards_[4].Value());
		}

		return isStraightFlush;
	}

	bool TryFourOfAKind(vector<int>& rank)
	{
		rank.clear();

		map<int,int> mapFour;

		for(size_t i=0; i<5; ++i)
		{
			++mapFour[cards_[i].Value()];
		}

		for(map<int,int>::iterator iter = mapFour.begin(); iter!=mapFour.end(); ++iter)
		{
			if(iter->second == 4)
			{
				rank.push_back(iter->first);
				return true;
			}
		}

		return false;
	}

	bool TryFullHouse(vector<int>& rank)
	{
		rank.clear();

		map<int,int> mapFullHouse;

		for(size_t i=0; i<5; ++i)
		{
			++mapFullHouse[cards_[i].Value()];
		}

		if(mapFullHouse.size() != 2) return false;

		if(mapFullHouse.begin()->second == 3)
		{
			rank.push_back(mapFullHouse.begin()->first);
			return true;
		}

		if(mapFullHouse.rbegin()->second == 3)
		{
			rank.push_back(mapFullHouse.rbegin()->first);
			return true;
		}

		return false;
	}

	bool TryFlush(vector<int>& rank)
	{
		rank.clear();

		bool isFlush = true;
		Suit suit = cards_[0].Suit();

		for(size_t i=1; i<5; ++i)
		{
			if(cards_[i].Suit() != suit)
			{
				isFlush = false;
				break;
			}
		}

		if(isFlush)
		{
			rank.push_back(cards_[4].Value());
		}

		return isFlush;
	}

	bool TryStraight(vector<int>& rank)
	{
		rank.clear();

		bool isStraight = true;
		int sValue = cards_[0].Value();

		for(size_t i=1; i<5; ++i)
		{
			if(cards_[i].Value() != ++sValue)
			{
				isStraight = false;
				break;
			}
		}

		if(isStraight)
		{
			rank.push_back(cards_[4].Value());
		}

		return isStraight;
	}

	bool TryThreeOfAKind(vector<int>& rank)
	{
		rank.clear();

		map<int,int> mapThree;

		for(size_t i=0; i<5; ++i)
		{
			++mapThree[cards_[i].Value()];
		}

		for(map<int,int>::iterator iter = mapThree.begin(); iter!=mapThree.end(); ++iter)
		{
			if(iter->second == 3)
			{
				rank.push_back(iter->first);
				return true;
			}
		}

		return false;
	}

	bool TryTwoPairs(vector<int>& rank)
	{
		rank.clear();
		rank.push_back(0);
		rank.push_back(0);
		rank.push_back(0);

		map<int,int> mapTwoPairs;

		for(size_t i=0; i<5; ++i)
		{
			++mapTwoPairs[cards_[i].Value()];
		}

		if(mapTwoPairs.size() != 3)
		{
			return false;
		}

		for(map<int,int>::iterator iter = mapTwoPairs.begin(); iter!=mapTwoPairs.end(); ++iter)
		{
			if(iter->second == 2)
			{
				rank[0] = rank[0];
				rank[1] = iter->first;
			}
			else if(iter->second == 1)
			{
				if(rank[2]) return false;

				rank[2] = iter->first;
			}
			else
			{
				return false;
			}
		}

		if(rank[0] < rank[1]) swap(rank[0], rank[1]);

		return true;
	}

	bool TryPairs(vector<int>& rank)
	{
		rank.clear();
		rank.push_back(0);
		rank.push_back(0);
		rank.push_back(0);
		rank.push_back(0);

		map<int,int> mapTwoPairs;

		for(size_t i=0; i<5; ++i)
		{
			++mapTwoPairs[cards_[i].Value()];
		}

		for(map<int,int>::iterator iter = mapTwoPairs.begin(); iter!=mapTwoPairs.end(); ++iter)
		{
			if(iter->second == 2)
			{
				rank[0] = iter->first;
			}
			else
			{
				rank[1] = rank[2];
				rank[2] = rank[3];
				rank[3] = iter->first;
			}
		}

		if(!rank[0]) return false;

		sort(++rank.begin(), rank.end(), greater<int>());

		return true;
	}

	bool TryHighCard(vector<int>& rank)
	{
		rank.clear();

		for(int i=4; i>=0; --i)
		{
			rank.push_back(cards_[i].Value());
		}

		return true;
	}

private:
	Card cards_[5];
};

typedef bool (PokerHand::*Rule)(vector<int>& rank);

class PokerGame
{
public:

	PokerGame() :
		winner_(None)
	{
		rules_.push_back(&PokerHand::TryStraightFlush);
		rules_.push_back(&PokerHand::TryFourOfAKind);
		rules_.push_back(&PokerHand::TryFullHouse);
		rules_.push_back(&PokerHand::TryFlush);
		rules_.push_back(&PokerHand::TryStraight);
		rules_.push_back(&PokerHand::TryThreeOfAKind);
		rules_.push_back(&PokerHand::TryTwoPairs);
		rules_.push_back(&PokerHand::TryPairs);
		rules_.push_back(&PokerHand::TryHighCard);
	}

	void ReadInput(stringstream& data)
	{
		black_.ReadInput(data);
		white_.ReadInput(data);
	}

	void Play()
	{
		for(size_t i=0; i<rules_.size(); ++i)
		{
			if(HasWinner(rules_[i]))
			{
				return;
			}
		}
	}

	::Winner Winner() const
	{
		return winner_;
	}

	bool HasWinner(Rule rule)
	{
		vector<int> bRank;
		vector<int> wRank;

		bool fBlack = (black_.*rule)(bRank);
		bool fWhite = (white_.*rule)(wRank);

		if(!fBlack && !fWhite)
		{
			winner_ = None;
			return false;
		}

		if(fBlack && fWhite)
		{
			for(size_t i=0; i<bRank.size(); ++i)
			{
				if(bRank[i] > wRank[i])
				{
					winner_ = Black;
					return true;
				}

				if(wRank[i] > bRank[i])
				{
					winner_ = White;
					return true;
				}			
			}

			winner_ = None;
			return false;
		}

		if(fBlack)
		{
			winner_ = Black;
			return true;
		}	

		if(fWhite)
		{
			winner_ = White;
			return true;
		}

		winner_ = None;
		return false;
	}

private:
	PokerHand black_;
	PokerHand white_;
	::Winner winner_;

	vector<Rule> rules_;
};

class Problem
{
public:
	void Solve()
	{
		while(ReadInput())
		{
			game_.Play();
			PrintOutput();
		}
	}

private:

	bool ReadInput()
	{
		string input;

		getline(cin,input);

		if(cin.bad())
		{
			return false;
		}

		if(input.empty())
		{
			return false;
		}

		stringstream data(input);

		game_.ReadInput(data);

		return true;
	}

	void PrintOutput()
	{
		switch (game_.Winner())
		{
		case Black:
			cout<<"Black wins."<<endl;
			break;

		case White:
			cout<<"White wins."<<endl;
			break;

		case None:
			cout<<"Tie."<<endl;
			break;
		}
	}

private:
	PokerGame game_;
};

int main()
{
	Problem problem;

	problem.Solve();

	return 0;
}