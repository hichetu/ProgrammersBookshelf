// 2.8.7.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110207&format=html

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

string trim(const std::string& str, const std::string& whitespace = " \t")
{
	const string::size_type strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const string::size_type strEnd = str.find_last_not_of(whitespace);
	const string::size_type strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

class Problem
{
public:
	enum Status
	{
		CORRECT,
		INCORRECT,
		UNSOLVED,
	};

public:

	Problem() :
		status_(UNSOLVED),
		incorrectSubmissions_(0)
	{
	}


	Status& ProblemStatus()
	{
		return status_;
	}

	size_t NumberOfIncorrectSubmissions() const
	{
		return incorrectSubmissions_;
	}

	void IncrementIncorrectSubmissions()
	{
		++incorrectSubmissions_;
	}

	static Status StatusFromChar(char c)
	{
		switch (c)
		{
		case 'C':
			return CORRECT;
			break;

		case 'I':
			return INCORRECT;
			break;
		}

		return UNSOLVED;
	}

private:

	Status status_;
	size_t incorrectSubmissions_;
};


class Contestant
{
public:

	Contestant() :
		number_(0),
		penalty_(0),
		solved_(0),
		fSubmitted_(false)
	{
	}

	int& Number()
	{
		return number_;
	}

	const int& Number() const
	{
		return number_;
	}

	const int& Penalty() const
	{
		return penalty_;
	}

	const int& NumberOfSolvedProblems() const
	{
		return solved_;
	}

	void Evaluate(int problemNumber, int time, Problem::Status status)
	{
		fSubmitted_ = true;

		if (problems_[problemNumber].ProblemStatus() == Problem::CORRECT) return;

		if (status == Problem::CORRECT)
		{
			penalty_ += time + problems_[problemNumber].NumberOfIncorrectSubmissions() * 20;
			problems_[problemNumber].ProblemStatus() = Problem::CORRECT;
			++solved_;
		}
		else if (status == Problem::INCORRECT)
		{
			problems_[problemNumber].IncrementIncorrectSubmissions();
		}
	}

	bool HasSubmitted() const
	{
		return fSubmitted_;
	}

private:

	int number_;
	int penalty_;
	int solved_;
	bool fSubmitted_;

	Problem problems_[10];
};

class ScoreLine
{
public:

	ScoreLine()
	{
		for (size_t i = 1; i < 101; ++i)
		{
			contestants_[i].Number() = i;
		}
	}

	void Evaluate(const string& line)
	{
		size_t number = 0;
		size_t problemNumber = 0;
		size_t time = 0;
		char statusChar = 0;

		stringstream stream(line);
		stream >> number;
		stream >> problemNumber;
		stream >> time;
		stream >> statusChar;

		if (number == 0 || problemNumber == 0 || time == 0 || statusChar == 0 || !stream.good())
		{
			return;
		}

		if (number > 100 || problemNumber > 9)
		{
			return;
		}

		Problem::Status status = Problem::StatusFromChar(statusChar);

		contestants_[number].Evaluate(problemNumber, time, status);
	}

	const set<Contestant>& Rank() const
	{
		return rank_;
	}

	void Solve()
	{
		for (size_t i = 1; i < 101; ++i)
		{
			if (contestants_[i].HasSubmitted())
			{
				rank_.insert(contestants_[i]);
			}
		}
	}

private:

	Contestant contestants_[101];
	set<Contestant> rank_;
};

bool operator<(const Contestant& l, const Contestant& r)
{
	if (l.NumberOfSolvedProblems() != r.NumberOfSolvedProblems())
	{
		return l.NumberOfSolvedProblems() > r.NumberOfSolvedProblems();
	}
	else
	{
		if (l.Penalty() != r.Penalty())
		{
			return l.Penalty() < r.Penalty();
		}
	}

	return l.Number() < r.Number();
}

class ContestScoreboard
{
public:

	ContestScoreboard() :
		numOfCases_(0),
		currCase_(0)
	{
	}

	void Solve()
	{
		ReadNumberOfCases();

		while (ReadCase())
		{
			SolveCase();
			WriteCase();
		}
	}

private:

	void ReadNumberOfCases()
	{
		string line;
		getline(cin, line);

		stringstream stream(line);
		stream >> numOfCases_;

		getline(cin, line);
	}

	bool ReadCase()
	{
		if (++currCase_ > numOfCases_) return false;

		scoreLine_ = ScoreLine();

		while (true)
		{
			string line;
			getline(cin, line);

			if (!cin.good()) break;
			if (trim(line).empty()) break;

			scoreLine_.Evaluate(line);
		}

		return true;
	}

	void SolveCase()
	{
		scoreLine_.Solve();
	}

	void WriteCase()
	{
		if (currCase_ > 1) 		cout << endl;

		const set<Contestant>& contestants = scoreLine_.Rank();

		for (set<Contestant>::iterator iter = contestants.begin(); iter != contestants.end(); ++iter)
		{
			cout << iter->Number() << ' ' << iter->NumberOfSolvedProblems() << ' ' << iter->Penalty() << endl;
		}
	}

private:
	size_t numOfCases_;
	size_t currCase_;

	ScoreLine scoreLine_;
};

int main()
{
	ContestScoreboard problem;
	problem.Solve();

	return 0;
}