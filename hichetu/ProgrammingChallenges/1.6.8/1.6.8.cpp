// 1.6.8.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

class PairComp
{
public:
	bool operator()(const pair<size_t, size_t>& x, const pair<size_t, size_t>& y)
	{
		return x.second < y.second;
	}
};

class Election
{
public:
	Election() : votesToWin_(0)
	{
		Clear();
	}

	const vector<string>& Winner() const
	{
		return winners_;
	}

	void AddCandidate(const string& name)
	{
		candidates_.push_back(name);
		table_.insert(make_pair(candidates_.size(), name));
	}

	void AddVotes(const vector<int>& vote)
	{
		votes_.push_back(vote);
	}

	void CountTheVotes()
	{
		votesToWin_ = votes_.size()/2 + 1;

		while(true)
		{
			RankCandidates();

			if(FindWinners())
			{
				break;
			}

			EliminateWeakCandidates();
		}
	}

	void Clear()
	{
		winners_.clear();
		candidates_.clear();
		votes_.clear();
		eliminated_.clear();
		roundCountSet_.clear();
		table_.clear();
		votesToWin_ = 0;
	}

	void RankCandidates()
	{
		roundCountSet_.clear();

		map<size_t, size_t> roundCount;

		for(size_t i=0; i<votes_.size(); ++i)
		{
			if(votes_[i].size())
			{
				++roundCount[votes_[i][0]];
			}
		}

		for(map<size_t, size_t>::iterator iter = roundCount.begin(); iter!=roundCount.end(); ++iter)
		{
			roundCountSet_.push_back(*iter);
		}

		std::sort(roundCountSet_.begin(), roundCountSet_.end(), PairComp());
	}

	bool FindWinners()
	{
		if(roundCountSet_.rbegin()->second >= votesToWin_)
		{
			winners_.push_back(table_[roundCountSet_.rbegin()->first]);
			return true;
		}
		else if(roundCountSet_.begin()->second == roundCountSet_.rbegin()->second)
		{
			if(roundCountSet_.size() == table_.size() - eliminated_.size())
			{
				for(vector< pair<size_t, size_t> >::iterator iter = roundCountSet_.begin(); iter!=roundCountSet_.end(); ++iter)
				{
					winners_.push_back(table_[iter->first]);
				}
				return true;
			}
		}
		return false;
	}

	void EliminateWeakCandidates()
	{
		size_t weakCount = roundCountSet_.begin()->second;

		for(vector< pair<size_t, size_t> >::iterator iter = roundCountSet_.begin(); iter!=roundCountSet_.end(); ++iter)
		{
			if(weakCount == iter->second)
			{
				eliminated_.insert(iter->first);
			}
			else
			{
				break;
			}
		}

		for(size_t i=0; i<votes_.size(); ++i)
		{
			vector<int> validVote;

			for(size_t x=0; x<votes_[i].size(); ++x)
			{
				if(eliminated_.find(votes_[i][x]) == eliminated_.end())
				{
					validVote.push_back(votes_[i][x]);
				}
			}

			votes_[i] = validVote;
		}
	}

private:
	vector<string> winners_;
	vector<string> candidates_;
	vector< vector< int > > votes_;

	size_t votesToWin_;

	set<size_t> eliminated_;
	map<size_t, string> table_;
	vector< pair< size_t, size_t > > roundCountSet_;
};

class AustralianVoting
{
public:

	AustralianVoting() : 
		numCases_(0),
		currentCaseNum_(0),
		numCandidates_(0)
	{
	}

	void Solve()
	{
		ReadNumberOfCases();

		while(ReadInput())
		{
			election_.CountTheVotes();
			PrintOutput();
		}
	}

private:
	bool ReadInput()
	{
		if(currentCaseNum_ >= numCases_) return false;

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
		string str;
		getline(cin, str);
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

	void PrintOutput() const
	{
		const vector<string>& ans = election_.Winner();

		for(size_t i=0; i<ans.size(); ++i)
		{
			cout<<ans[i]<<endl;
		}

		if(currentCaseNum_ < numCases_) cout<<endl;
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