/*



Interpreter




A certain computer has ten registers and 1,000 words of RAM. Each register or RAM location holds a three-digit integer between 0 and 999. Instructions are encoded as three-digit integers and stored in RAM. The encodings are as follows:

100 	means halt
2dn 	means set register d to n (between 0 and 9)
3dn 	means add n to register d
4dn 	means multiply register d by n
5ds 	means set register d to the value of register s
6ds 	means add the value of register s to register d
7ds 	means multiply register d by the value of register s
8da 	means set register d to the value in RAM whose address is in register a
9sa 	means set the value in RAM whose address is in register a to the value of register s
0ds 	means goto the location in register d unless register s contains 0

All registers initially contain 000. The initial content of the RAM is read from standard input. The first instruction to be executed is at RAM address 0. All results are reduced modulo 1,000.

Input

The input begins with a single positive integer on a line by itself indicating the number of cases, each described as below. This is followed by a blank line, and there will be a blank line between each two consecutive inputs.

Each input case consists of up to 1,000 three-digit unsigned integers, representing the contents of consecutive RAM locations starting at 0. Unspecified RAM locations are initialized to 000.

Output

The output of each test case is a single integer: the number of instructions executed up to and including the halt instruction. You may assume that the program does halt. Separate the output of two consecutive cases by a blank line.

Sample Input

1

299
492
495
399
492
495
399
283
279
689
078
100
000
000
000

Sample Output

16


*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
using namespace std;

const string halt = "100";

class Interpreter
{
private:
	size_t N_;
	string ram_[1000];
	size_t numInstructions_;
	size_t currExecuteAddress_;
	size_t iter;
	string acc_;

	string register_[10];

public:

	Interpreter() :
		N_(0), 
		numInstructions_(0), 
		currExecuteAddress_(0), 
		iter(0)
	{	
		Reset();
	}

	void Solve()
	{
		ReadNumberOfInputs();

		for(size_t n = 0; n< N_; ++n)
		{
			Reset();
			ReadInput();
			Attack();
			PrintOutput();
		}
	}

private:

	void ReadNumberOfInputs()
	{
		cin >> N_;
		string line;
		getline(cin, line);
		getline(cin, line);
	}

	void ReadInput()
	{
		int currAddress = 0;

		while(cin.good() && currAddress <1000)
		{
			string line;
			getline(cin, line);

			if(line.size()<3) break;

			ram_[currAddress++] = line;
		}
	}

	void Reset()
	{
		for(size_t i=0; i<1000; ++i)
		{
			ram_[i] = "000";
		}
		for(size_t i=0; i<10; ++i)
		{
			register_[i] = "000";
		}

		numInstructions_ = 0;
		currExecuteAddress_ = 0;

	}

	void Attack()
	{
		Execute();
	}

	void Execute()
	{
		while(true)
		{
			++numInstructions_;
			acc_ = ram_[currExecuteAddress_++];

			switch(acc_[0])
			{
			case '1':
				{
					if(acc_ == "100")
						return;
				}
				break;

			case '2':
				{
					register_[acc_[1]-'0'] = toString(toInt(acc_[2]));
				}
				break;

			case '3':
				{
					register_[acc_[1]-'0'] = toString( toInt(register_[acc_[1]-'0']) + toInt(acc_[2]));
				}
				break;

			case '4':
				{
					register_[acc_[1]-'0'] = toString( toInt(register_[acc_[1]-'0']) * toInt(acc_[2]));
				}
				break;

			case '5':
				{
					register_[acc_[1]-'0'] = register_[acc_[2]-'0'];
				}
				break;

			case '6':
				{
					register_[acc_[1]-'0'] = toString( toInt(register_[acc_[1]-'0']) + toInt(register_[acc_[2]-'0']));
				}
				break;

			case '7':
				{
					register_[acc_[1]-'0'] = toString( toInt(register_[acc_[1]-'0']) * toInt(register_[acc_[2]-'0']));
				}
				break;

			case '8':
				{
					register_[acc_[1]-'0'] = ram_[toInt(register_[acc_[2]-'0'])];
				}
				break;

			case '9':
				{
					ram_[toInt(register_[acc_[2]-'0'])] = register_[acc_[1]-'0'];
				}
				break;

			case '0':
				{
					if(toInt(register_[acc_[2]-'0']))
					{
						currExecuteAddress_ = toInt(register_[acc_[1]-'0']);
					}
				}
				break;
			}
		}

	}

	string toString(int v)
	{
		v = v%1000;

		string ret;

		if(v<10)
		{
			ret = "00";
		}
		else if(v<100)
		{
			ret = "0";
		}

		stringstream str;
		str << v;

		ret += str.str();

		return ret;
	}

	int toInt(const string& str)
	{
		int v = 0;

		stringstream ss(str);
		ss >> v;
		return v%1000;
	}

	int toInt(const char& str)
	{
		return str -'0';
	}


	void PrintOutput()
	{
		if(iter++)
		{
			cout<<endl;
		}

		cout<<numInstructions_<<endl;

	}
};


int main()
{
	Interpreter problem;

	problem.Solve();

	return 0;
}