// 2.8.5.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110205&format=html

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <sstream>
using namespace std;

#if (_MSC_VER >=1700)
#define MODERN_COMPILER 
#endif

class Shuffler
{
public:
	Shuffler(vector< vector<size_t> > shuffleArray, vector<size_t> shuffleNumbers) :
		shuffleArray_(shuffleArray),
		shuffleNumbers_(shuffleNumbers)
	{
	}

	vector<size_t> Shuffle()
	{
		InitCards();

		ShuffleCards();

		return cardOrder_;
	}

	void InitCards()
	{
		cardOrder_.clear();

		for (size_t i = 0; i < 52; ++i) cardOrder_.push_back(i);
	}

	void ShuffleCards()
	{
		for (size_t i = 0; i < shuffleNumbers_.size(); ++i)
		{
			ApplyShuffle(shuffleNumbers_[i]);
		}
	}

	void ApplyShuffle(size_t shuffleNumber)
	{
		vector<size_t> shuffleOrder = shuffleArray_[--shuffleNumber];

		vector<size_t> cardOrder = cardOrder_;

		for (size_t position = 0; position < shuffleOrder.size(); ++position)
		{
			cardOrder_[position] = cardOrder[shuffleOrder[position]];
		}
	}

private:
	vector< vector<size_t> > shuffleArray_;
	vector<size_t> shuffleNumbers_;

	vector<size_t> cardOrder_;
};

class StackThemUp
{
public:

	StackThemUp() :
		numOfCases_(0),
		currentCase_(0)
	{
	}

	void Solve()
	{
		ReadNumOfCases();

		while (ReadCase())
		{
			ShuffleCase();
			WriteCase();
		}
	}

private:

	void ReadNumOfCases()
	{
		string line;
		getline(cin, line);
		stringstream stream(line);
		stream >> numOfCases_;
		getline(cin, line);
	}

	bool ReadCase()
	{
		if (++currentCase_ > numOfCases_)
		{
			return false;
		}

		Clear();

		size_t numShuffles = 0;
		string line;
		getline(cin, line);

		if (cin.bad() || line.empty())
		{
			return false;
		}

		stringstream stream(line);
		stream >> numShuffles;

		for (size_t i = 0; i < numShuffles; ++i)
		{
			vector<size_t> shuffle;

			for (size_t k = 0; k < 52; ++k)
			{
				size_t shuffleOrder = 0;

				cin >> shuffleOrder;

				if (shuffleOrder == 0) return false;
				if (cin.bad()) return false;

				shuffle.push_back(--shuffleOrder);
			}

			shuffleArray_.push_back(shuffle);
		}

		line.clear();

		while (line.empty())
		{
			getline(cin, line);

			if (!cin.good()) return false;
		}

		while (!line.empty())
		{
			stringstream stream(line);
			size_t shuffleNumber = 0;
			stream >> shuffleNumber;

			if (shuffleNumber == 0) return false;
			if (shuffleNumber > shuffleArray_.size()) return false;

			shuffleNumbers_.push_back(shuffleNumber);

			line.clear();
			getline(cin, line);
		}

		return true;
	}

	void ShuffleCase()
	{
		Shuffler shuffler(shuffleArray_, shuffleNumbers_);
		cardOrder_ = shuffler.Shuffle();
	}

	void WriteCase()
	{
		if (currentCase_ > 1) cout << endl;

		for (size_t i = 0; i < cardOrder_.size(); ++i)
		{
			WriteCard(cardOrder_[i]);
		}
	}

	void WriteCard(size_t cardNumber)
	{
		size_t suit = cardNumber / 13;
		size_t number = cardNumber % 13;

		switch (number)
		{
		case 0:  cout << "2";		break;

		case 1:  cout << "3";		break;

		case 2:  cout << "4";		break;

		case 3:  cout << "5";		break;

		case 4:  cout << "6";		break;

		case 5:  cout << "7";		break;

		case 6:  cout << "8";		break;

		case 7:  cout << "9";		break;

		case 8:  cout << "10";		break;

		case 9:  cout << "Jack";	break;

		case 10: cout << "Queen";	break;

		case 11: cout << "King";	break;

		case 12: cout << "Ace";		break;

		default: cout << "Error";	break;
		}

		cout << " of ";

		switch (suit)
		{
		case 0:
			cout << "Clubs";
			break;

		case 1:
			cout << "Diamonds";
			break;

		case 2:
			cout << "Hearts";
			break;

		case 3:
			cout << "Spades";
			break;

		default:
			cout << "Error";
			break;
		}

		cout << endl;
	}

	void Clear()
	{
		shuffleArray_.clear();
		shuffleNumbers_.clear();
		cardOrder_.clear();
	}

private:
	size_t numOfCases_;
	size_t currentCase_;

	vector< vector<size_t> > shuffleArray_;
	vector<size_t> shuffleNumbers_;
	vector<size_t> cardOrder_;
};

#ifdef MODERN_COMPILER
#include <chrono>
#endif

int main()
{
#ifdef MODERN_COMPILER
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();
#endif

	StackThemUp problem;
	problem.Solve();

#ifdef MODERN_COMPILER
	end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	cout << "\n" << endl;
	cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
#endif

	return 0;
}