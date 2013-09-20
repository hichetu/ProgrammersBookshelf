/*
Have you ever played Minesweeper? This cute little game comes with a certain operating system whose name we can't remember. The goal of the game is to find where all the mines are located within a M x N field.

The game shows a number in a square which tells you how many mines there are adjacent to that square. Each square has at most eight adjacent squares. The 4 x 4 field on the left contains two mines, each represented by a ``*'' character. If we represent the same field by the hint numbers described above, we end up with the field on the right:

*...
....
.*..
....

*100
2210
1*10
1110

Input

The input will consist of an arbitrary number of fields. The first line of each field contains two integers n and m ( 0 < n, m$ \le$100) which stand for the number of lines and columns of the field, respectively. Each of the next n lines contains exactly m characters, representing the field.

Safe squares are denoted by ``.'' and mine squares by ``*,'' both without the quotes. The first field line where n = m = 0 represents the end of input and should not be processed.

Output

For each field, print the message Field #x: on a line alone, where x stands for the number of the field starting from 1. The next n lines should contain the field with the ``.'' characters replaced by the number of mines adjacent to that square. There must be an empty line between field outputs.

Sample Input

4 4
*...
....
.*..
....
3 5
**...
.....
.*...
0 0

Sample Output

Field #1:
*100
2210
1*10
1110

Field #2:
**100
33200
1*100

*/

#include <iostream>
using namespace std;

class Minesweeper
{
public:

	Minesweeper() : N_(0), M_(0), fieldNumber_(0) {}

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

		if(cin.good())
		{
			cin >> M_;
		}

		return cin.good() && N_>0 && M_>0;			
	}

	void Reset()
	{
		memset(workSheet_, 0x0, sizeof(workSheet_));
	}

	void Attack()
	{
		for(int n=0; n<N_; ++n)
		{
			for(int m=0; m<M_; ++m)
			{
				char c;
				cin >> c;

				if(c=='*')
				{
					workSheet_[n][m] = -1;

					int dx[] = { -1, 0, +1 };
					int dy[] = { -1, 0, +1 };

					for(int x=0; x<3; ++x)
					{
						for(int y=0; y<3; ++y)
						{
							int ns = n + dx[x];
							int ms = m + dy[y];

							if(ns>=0 && ms>=0 && !(x==1 && y==1) && (workSheet_[ns][ms] != -1))
							{
								++workSheet_[ns][ms];
							}
						}
					}
				}
			}
		}
	}

	void PrintOutput()
	{
		++fieldNumber_;
		cout<<"Field #"<<fieldNumber_<<":"<<endl;

		for(int n=0; n<N_; ++n)
		{
			for(int m=0; m<M_; ++m)
			{
				if(workSheet_[n][m] == -1)
				{
					cout<<'*';
				}
				else
				{
					cout<<workSheet_[n][m];
				}
			}
			cout<<endl;
		}

		cout<<endl;
	}

	int N_;
	int M_;

	size_t fieldNumber_;
	int workSheet_[101][101];
};


int main()
{
	Minesweeper problem;

	problem.Solve();

	return 0;
}