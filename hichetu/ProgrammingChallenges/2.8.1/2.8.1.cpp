//Problem 2.8.1  - http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110201

#include <bitset>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

class JollyJumpers
{
public:

	JollyJumpers() : inputCounter_(0) {}

	void Solve()
	{
		while(ReadInput())
		{
			CheckJolly();
			PrintOutput();
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

	void CheckJolly()
	{
		GetNumbers();

		MagicJollyBitSet();

		if(IsJolly())
		{
			output_ = "Jolly";
		}
		else
		{
			output_ = "Not jolly";
		}
	}

	void PrintOutput()
	{
		cout<<output_<<endl;
	}

	void GetNumbers()
	{
		numbers_.clear();

		stringstream stream(input_);

		int n = 0;
		stream >> n;

		while(stream.good())
		{
			int n = 0;
			stream >> n;
			numbers_.push_back(n);
		}
	}

	void MagicJollyBitSet()
	{
		bitset<3000> bS;

		for(size_t i=1; i<numbers_.size(); ++i)
		{
			bS[ abs(numbers_[i] - numbers_[i-1]) ] = true;
		}

		isJolly_ = true;

		for(size_t i=1; i<numbers_.size(); ++i)
		{
			if(!bS[i])
			{
				isJolly_ = false;
				break;
			}
		}
	}

	bool IsJolly() const
	{
		return isJolly_;
	}

private:
	string input_;
	string output_;
	int inputCounter_;
	vector<int> numbers_;
	bool isJolly_;
};

int main()
{
	JollyJumpers problem;

	problem.Solve();

	return 0;
}