// 2.8.7.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110207&format=html


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
		solvedTime_(0),
		incorrectSubmissions_(0)
	{
	}


	Status& ProblemStatus()
	{
		return status_;
	}

	int& SolvedTime()
	{
		return solvedTime_;
	}

	const int& NumberOfIncorrectSubmissions() const
	{
		return incorrectSubmissions_;
	}

	void IncrementIncorrectSubmissions()
	{
		++incorrectSubmissions_;
	}

private:

	Status status_;
	int solvedTime_;
	int incorrectSubmissions_;
};


class Contestant
{
public:

	Contestant(int number) :
		number_(number)
	{

	}

	const int& Number() const
	{
		return number_;
	}

	const int& Penalty() const
	{
		return penalty_;
	}

	const int& Solved() const
	{
		return solved_;
	}

	void Evaluate(int problemNumber, int time, Problem::Status status)
	{

	}

private:

	int number_;
	int penalty_;
	int solved_;

	Problem problems_[10];
};

