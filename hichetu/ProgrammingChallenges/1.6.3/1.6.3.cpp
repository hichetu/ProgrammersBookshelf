/*
The Trip




A group of students are members of a club that travels annually to different locations. Their destinations in the past have included Indianapolis, Phoenix, Nashville, Philadelphia, San Jose, and Atlanta. This spring they are planning a trip to Eindhoven.

The group agrees in advance to share expenses equally, but it is not practical to share every expense as it occurs. Thus individuals in the group pay for particular things, such as meals, hotels, taxi rides, and plane tickets. After the trip, each student's expenses are tallied and money is exchanged so that the net cost to each is the same, to within one cent. In the past, this money exchange has been tedious and time consuming. Your job is to compute, from a list of expenses, the minimum amount of money that must change hands in order to equalize (within one cent) all the students' costs.

Input
Standard input will contain the information for several trips. Each trip consists of a line containing a positive integer n denoting the number of students on the trip. This is followed by n lines of input, each containing the amount spent by a student in dollars and cents. There are no more than 1000 students and no student spent more than $10,000.00. A single line containing 0 follows the information for the last trip.

Output
For each trip, output a line stating the total amount of money, in dollars and cents, that must be exchanged to equalize the students' costs.

Sample Input

3
10.00
20.00
30.00
4
15.00
15.01
3.00
3.01
0

Sample Output

$10.00
$11.99
*/


#include <iostream>
#include <vector>
using namespace std;

class TheTrip
{
public:

	TheTrip() : N_(0), moneyExchangeInCents_(0) {}

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

	bool ReadInput()	
	{
		if(cin.good())
		{
			cin >> N_;
		}

		return cin.good() && N_>0;
	}

	void Reset()
	{
		moneyExchangeInCents_ = 0;
	}

	void Attack()
	{
		unsigned long totalExpense = 0;
		vector<unsigned long> expenses;

		for(int n=0; n<N_; ++n)
		{
			unsigned long currExpenseDollars = 0;
			unsigned long currExpenseCents = 0;
			char dot;

			cin>>currExpenseDollars;
			cin>>dot;
			cin>>currExpenseCents;

			unsigned long currExpenseInCents = currExpenseDollars*100 +  currExpenseCents;//unsigned long(currExpense*100);

			totalExpense+= currExpenseInCents;
			expenses.push_back(currExpenseInCents);
		}

		unsigned long avgExpenseLow = (totalExpense)/N_;
		unsigned long avgExpenseHigh = (totalExpense + N_-1)/(N_);

		unsigned long low = 0;
		unsigned long high = 0;

		for(size_t i=0; i<expenses.size(); ++i)
		{
			if(expenses[i]<avgExpenseLow)
			{
				low += (avgExpenseLow - expenses[i]);
			}
			else if(expenses[i] > avgExpenseHigh)
			{
				high += (expenses[i] - avgExpenseHigh);
			}
		}

		moneyExchangeInCents_ = max(low,high);
	}

	void PrintOutput()
	{
		unsigned long dollars = moneyExchangeInCents_/100;
		unsigned long cents = moneyExchangeInCents_%100;

		if(cents>=10)
		{
			cout<< "$"<<dollars<<"."<<cents<<endl;
		}
		else
		{
			cout<< "$"<<dollars<<".0"<<cents<<endl;
		}
	}

	int N_;
	unsigned long moneyExchangeInCents_;
};


int main()
{
	TheTrip problem;

	problem.Solve();

	return 0;
}