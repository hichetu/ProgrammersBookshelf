// 1.6.8.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Election
{
public:
	string Winner();
	void AddCandidate(const string& name);
	void AddVotes(const vector<int>& vote);
	void CountTheVotes();
	void Clear();
};

class AustralianVoting
{
public:
	void Solve()
	{
		ReadNumberOfCases();

		while(ReadInput())
		{
			election_.CountTheVotes();
			cout<<election_.Winner()<<endl;
		}
	}

private:
	bool ReadInput()
	{
		if(currentCaseNum_ > numCases_) return false;

		election_.Clear();

		if(ReadCandiateNames())
		{
			if(ReadVotes())
			{
				++currentCaseNum_;
				return true;
			}
		}

		return false;
	}

	void ReadNumberOfCases()
	{
		numCases_ = ReadNumber();
	}

	bool ReadCandiateNames()
	{
		numCandidates_ = ReadNumber();

		if(!numCandidates_)
		{
			return false;
		}

		for(size_t i=0; i<numCandidates_; ++i)
		{
			string str;
			getline(cin, str);

			if(!str.size()) return false;

			election_.AddCandidate(str);
		}

		return true;
	}

	bool ReadVotes()
	{
		while(true)
		{
			string str;
			getline(cin, str);

			if(cin.bad()) return false;

			if(!str.size()) return true;

			istringstream stream(str);

			vector<int> votes;

			for(size_t i=0; i<numCandidates_; ++i)
			{
				size_t candidate = 0;
				stream >> candidate;

				if(!candidate) return false;

				votes.push_back(candidate);
			}

			election_.AddVotes(votes);
		}
	}

	size_t ReadNumber()
	{
		size_t number = 0;

		string str;
		getline(cin, str);
		istringstream stream(str);
		stream >> number;

		return number;
	}

private:
	Election election_;
	size_t numCases_;
	size_t currentCaseNum_;
	size_t numCandidates_;
};


int main()
{
	AustralianVoting problem;

	problem.Solve();

	return 0;
}