/*
From Skiena and Revilla, Programming Challenges: The Programming Contest Training Manual
Springer-Verlag, New York, 2003. ISBN: 0-387-00163-8
110104 LCD Display
A friend of yours has just bought a new computer. Before this, the most powerful machine he
ever used was a pocket calculator. He is a little disappointed because he liked the LCD display of
his calculator more than the screen on his new computer! To make him happy, write a program that
prints numbers in LCD display style.
Input
The input le contains several lines, one for each number to be displayed. Each line contains
integers s and n, where n is the number to be displayed (0  n  99; 999; 999) and s is the size in
which it shall be displayed (1  s  10). The input will be terminated by a line containing two zeros,
which should not be processed.
Output
Print the numbers specied in the input le in an LCD display-style using s \-" signs for the
horizontal segments and s \|" signs for the vertical ones. Each digit occupies exactly s + 2 columns
and 2s + 3 rows. Be sure to ll all the white space occupied by the digits with blanks, including the
last digit. There must be exactly one column of blanks between two digits.
Output a blank line after each number. You will nd an example of each digit in the sample output
below.
Sample Input
2 12345
3 67890
0 0
Sample Output
-- -- --
| | | | | |
| | | | | |
-- -- -- --
| | | | |
| | | | |
-- -- --
--- --- --- --- ---
| | | | | | | |
| | | | | | | |
| | | | | | | |
--- --- ---
| | | | | | | |
| | | | | | | |
| | | | | | | |
--- --- --- ---
http://www.programming-challenges.com copyright 
c 2003
*/


#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

using namespace std;

int LCDDisplayMap[10][7] = {
	{1,1,1,0,1,1,1},
	{0,0,1,0,0,1,0},
	{0,1,1,1,1,0,1},
	{0,1,1,1,0,1,1},
	{1,0,1,1,0,1,0},
	{1,1,0,1,0,1,1},
	{1,1,0,1,1,1,1},
	{0,1,1,0,0,1,0},
	{1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1},
};

class LCDDisplay
{
public:

	LCDDisplay() : S_(0)
	{

	}

	void Solve()
	{
		while(ReadInput())
		{
			Reset();

			Attack();
		}
	}

private:



	bool ReadInput()	
	{
		if(cin.good())
		{
			cin >> S_;
		}

		return cin.good() && S_>0;
	}

	void Reset()
	{
	}

	void Attack()
	{
		long N;
		cin >> N;

		stringstream ss;
		ss << N;
		string num = ss.str();

		size_t len = 0;
		while(num[len]) ++len;

		for(size_t i=0; i<num.size(); ++i)
		{
			if(i)
			{
				cout<<' ';
			}

			cout<<' ';
			Print1(num[i]);
			cout<<' ';
		}
		cout<<endl;
		for(int s=0; s<S_; ++s)
		{
			for(size_t i=0; i<num.size(); ++i)
			{
				if(i)
				{
					cout<<' ';
				}

				Print0(num[i]);
				PrintBlanks();
				Print2(num[i]);
			}
			cout<<endl;
		}
		for(size_t i=0; i<num.size(); ++i)
		{
			if(i)
			{
				cout<<' ';
			}

			cout<<' ';
			Print3(num[i]);
			cout<<' ';
		}
		cout<<endl;
		for(int s=0; s<S_; ++s)
		{		
			for(size_t i=0; i<num.size(); ++i)
			{
				if(i)
				{
					cout<<' ';
				}

				Print4(num[i]);
				PrintBlanks();
				Print5(num[i]);
			}
			cout<<endl;
		}
		for(size_t i=0; i<num.size(); ++i)
		{
			if(i)
			{
				cout<<' ';
			}

			cout<<' ';
			Print6(num[i]);
			cout<<' ';
		}
		cout<<endl;

		cout<<endl;
	}

private:
	void Print0(char c)
	{
		PrintV(c,0);
	}

	void Print1(char c)
	{
		PrintH(c,1);
	}

	void Print2(char c)
	{
		PrintV(c,2);
	}

	void Print3(char c)
	{
		PrintH(c,3);
	}

	void Print4(char c)
	{
		PrintV(c,4);
	}

	void Print5(char c)
	{
		PrintV(c,5);
	}

	void Print6(char c)
	{
		PrintH(c,6);
	}

	void PrintH(char c, int d)
	{
		int n = c-'0';

		int p = LCDDisplayMap[n][d];

		if(p)
		{
			PrintHDash();
		}
		else
		{
			PrintBlanks();
		}
	}



	void PrintV(char c, int d)
	{
		int n = c-'0';

		int p = LCDDisplayMap[n][d];

		if(p)
		{
			cout<<'|';
		}
		else
		{
			cout<<' ';
		}
	}


	void PrintHDash()
	{
		for(int s=0; s<S_; ++s)
		{
			cout<<'-';
		}
	}

	void PrintBlanks()
	{
		for(int s=0; s<S_; ++s)
		{
			cout<<' ';
		}
	}
private:
	int S_;
};


int main()
{
	LCDDisplay problem;

	problem.Solve();

	return 0;
}