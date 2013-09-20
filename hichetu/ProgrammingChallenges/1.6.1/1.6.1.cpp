#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

class ThreeNPlusOne
{
public:

	ThreeNPlusOne() : A_(0), B_(0), maxLength_(0)
	{
		cache_[1] = 1;
	}

	void Solve()
	{
		while(ReadInput())
		{
			Reset();

			Attack();

			PrintOutput();
		}
	}

private:

	void Reset()
	{
		maxLength_ = 0;
	}

	bool ReadInput()
	{
		if(cin.good())
		{
			cin >> A_;
		}

		if(cin.good())
		{
			cin >> B_;
		}

		return cin.good();
	}

	void Attack()
	{
		for(size_t i=min(A_, B_); i<=max(A_, B_); ++i)
		{
			maxLength_ = std::max(maxLength_, ThreeNPlusOneLength(i));
		}
	}

	void PrintOutput()
	{
		cout << A_ << " " << B_ << " " << maxLength_ <<endl;
	}

	size_t ThreeNPlusOneLength(size_t n)
	{
		map<size_t, size_t>::iterator iter = cache_.find(n);

		if(iter != cache_.end())
		{
			return iter->second;
		}

		size_t length = 0;

		if(n%2 == 0)
		{
			length = 1 + ThreeNPlusOneLength(n/2);
		}
		else
		{
			length = 1 + ThreeNPlusOneLength(n*3 + 1);
		}

		cache_[n] = length;

		return length;

	}

	inline bool IsEven(size_t n)
	{
		return n%2 == 0;
	}

private:
	size_t A_;
	size_t B_;

	size_t maxLength_;

	map<size_t, size_t> cache_;
};

int main()
{
	ThreeNPlusOne problem;

	problem.Solve();

	return 0;
}