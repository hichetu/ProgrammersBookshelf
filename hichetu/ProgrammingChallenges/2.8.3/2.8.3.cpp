// 2.8.3.cpp : http://www.programming-challenges.com/pg.php?page=downloadproblem&probid=110203
//

#include <bitset>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Problem
{
public:

	Problem() :
		numCases_(0),
		caseNumber_(0),
		days_(0),
		numHartals_(0),
		workDayLostCounter_(0)
	{
	}

	void Solve()
	{
		ReadNumberOfCases();

		while(ReadInput())
		{
			KaroHartal();
			PrintOutput();
		}
	}

private:
	bool ReadInput()
	{
		numHartals_ = 0;
		days_ = 0;

		if (++caseNumber_ > numCases_)
		{
			return false;
		}

		string str;
		getline(cin, str);

		if(cin.bad() || str.empty()) return false;

		{
			stringstream stream(str);
			stream >> days_;
		}

		str.clear();
		getline(cin, str);

		if(cin.bad() || str.empty()) return false;

		{
			stringstream stream(str);
			stream >> numHartals_;
		}

		if(!numHartals_) return false;

		hartals_.clear();

		for(int i=0; i<numHartals_; ++i)
		{
			string str;
			getline(cin, str);
			if(cin.bad() || str.empty()) return false;
			stringstream stream(str);

			int n = 0;
			stream >> n;

			if(!n) return false;

			hartals_.push_back(n);
		}

		return true;
	}

	void ReadNumberOfCases()
	{
		string str;
		getline(cin, str);
		stringstream stream(str);

		stream >> numCases_;
	}

	void KaroHartal()
	{
		bitSet_.reset();
		workDayLostCounter_ = 0;

		for(size_t i=0; i<hartals_.size(); ++i)
		{
			for(int h = hartals_[i]; h<=days_; h+=hartals_[i])
			{
				bitSet_[h] = true;
			}
		}

		for(int h = 1; h<=days_; ++h)
		{
			if(h%7 == 0 || h%7 == 6) continue;

			if(bitSet_[h])
			{
				++workDayLostCounter_;
			}
		}
	}

	void PrintOutput()
	{
		cout<<workDayLostCounter_<<endl;
	}

private:
	int numCases_;
	int caseNumber_;
	int days_;
	int numHartals_;
	int workDayLostCounter_;

	vector<int> hartals_;
	bitset<3651> bitSet_;
};

int main()
{
	Problem problem;

	problem.Solve();

	return 0;
}