/*
/*

Graphical Editor




Graphical editors such as Photoshop allow us to alter bit-mapped images in the same way that text editors allow us to modify documents. Images are represented as an M x N array of pixels, where each pixel has a given color.

Your task is to write a program which simulates a simple interactive graphical editor.

Input

The input consists of a sequence of editor commands, one per line. Each command is represented by one capital letter placed as the first character of the line. If the command needs parameters, they will be given on the same line separated by spaces.

Pixel coordinates are represented by two integers, a column number between 1...M and a row number between 1...N, where 1$ \le$M, N$ \le$250. The origin sits in the upper-left corner of the table. Colors are specified by capital letters.

The editor accepts the following commands:

I M N 	Create a new M x N image with all pixels initially colored white (O).
C 	Clear the table by setting all pixels white (O). The size remains unchanged.
L X Y C 	Colors the pixel (X, Y) in color (C).
V X Y1 Y2 C 	Draw a vertical segment of color (C) in column X, between the rows Y1 and Y2 inclusive.
H X1 X2 Y C 	Draw a horizontal segment of color (C) in the row Y, between the columns X1 and X2 inclusive.
K X1 Y1 X2 Y2 C 	Draw a filled rectangle of color C, where (X1, Y1) is the upper-left and (X2, Y2) the lower right corner.
F X Y C 	Fill the region R with the color C, where R is defined as follows. Pixel (X, Y) belongs to R. Any other pixel which is the same color as pixel (X, Y) and shares a common side with any pixel in R also belongs to this region.
S Name 	Write the file name in MSDOS 8.3 format followed by the contents of the current image.
X 	Terminate the session.

Output

On every command S NAME, print the filename NAME and contents of the current image. Each row is represented by the color contents of each pixel. See the sample output.

Ignore the entire line of any command defined by a character other than I, C, L, V, H, K, F, S, or X, and pass on to the next command. In case of other errors, the program behavior is unpredictable.

Sample Input

I 5 6
L 2 3 A
S one.bmp
G 2 3 J
F 3 3 J
V 2 3 4 W
H 3 4 2 Z
S two.bmp
X

Sample Output

one.bmp
OOOOO
OOOOO
OAOOO
OOOOO
OOOOO
OOOOO
two.bmp
JJJJJ
JJZZJ
JWJJJ
JWJJJ
JJJJJ
JJJJJ


*/

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
#include <stack>
using namespace std;

class GraphicalEditor
{
public:

	GraphicalEditor() :
		command_(0),
		M_(0),
		N_(0)
	{
	}

	void Solve()
	{
		while(ReadInput())
		{
			if(!Attack())
			{
				return;
			}
		}
	}

private:

	bool ReadInput()
	{
		while(true)
		{
			string str;
			getline(cin, str);

			if(cin.bad() || !str.size())
			{
				return false;
			}

			buffer_. clear();

			buffer_.str(str);

			buffer_ >> command_;

			if(Accepted(command_))
			{
				return true;
			}
		}

		return true;
	}

private:


	bool Attack()
	{
		switch(command_)
		{
		case 'I':
			{
				return Init();
			}
			break;

		case 'C':
			{
				return Clear();
			}
			break;

		case 'L':
			{
				return ColorPixel();
			}
			break;

		case 'V':
			{
				return DrawVerticalSegment();
			}
			break;

		case 'H':
			{
				return DrawHorizontalSegment();
			}
			break;

		case 'K':
			{
				return DrawFilledRectangle();
			}
			break;

		case 'F':
			{
				return FillRegion();
			}
			break;

		case 'S':
			{
				return WriteFileName();
			}
			break;

		case 'X':
			{
				return false;
			}
			break;

		default:
			return false;
			break;
		}

		return false;
	}

	bool Accepted(char command)
	{
		switch(command)
		{
		case 'I':
		case 'C':
		case 'L':
		case 'V':
		case 'H':
		case 'K':
		case 'F':
		case 'S':
		case 'X':
			return true;
			break;

		default:
			return false;
			break;
		}

		return false;
	}


	bool Init()
	{
		buffer_ >> M_;
		buffer_ >> N_;

		if(M_<1 || N_<1)
			return false;	

		if(M_>250 || N_>250)
			return false;


		bitMap_ = vector< vector<char> >(N_, vector<char>(M_, 'O'));

		return true;

	}

	bool WriteFileName()
	{

		string filename;
		buffer_ >> filename;

		cout<<filename<<endl;

		for(int x=0; x<N_; ++x)
		{
			for(int y=0; y<M_; ++y)
			{
				cout<<bitMap_[x][y];
			}
			cout<<endl;
		}

		return true;
	}

	bool Clear()
	{
		bitMap_ = vector< vector<char> >(N_, vector<char>(M_, 'O'));
		return true;
	}

	bool ColorPixel()
	{
		int X = -1;
		int Y = -1;
		char C = 0;

		buffer_ >> X;
		buffer_ >> Y;
		buffer_ >> C;

		if(X<1 || Y<1)
		{
			return false;
		}

		if(X>M_ || Y>N_)
		{
			return false;
		}

		if(!C)
		{
			return false;
		}

		bitMap_[Y-1][X-1] = C;

		return true;
	}

	bool DrawVerticalSegment()
	{
		int X = -1;
		int Y1 = -1;
		int Y2 = -1;
		char C = 0;

		buffer_ >> X;
		buffer_ >> Y1;
		buffer_ >> Y2;
		buffer_ >> C;

		if(X<1 || Y1<1 || Y2<1)
		{
			return false;
		}

		if(X>M_ || Y1>N_ || Y2>N_)
		{
			return false;
		}

		if(!C)
		{
			return false;
		}

		for(int Y=min(Y1,Y2); Y<=max(Y1,Y2); ++Y)
		{
			bitMap_[Y-1][X-1] = C;
		}

		return true;

	}

	bool DrawHorizontalSegment()
	{
		int X1 = -1;
		int X2 = -1;
		int Y = -1;
		char C = 0;

		buffer_ >> X1;
		buffer_ >> X2;
		buffer_ >> Y;
		buffer_ >> C;

		if(X1<1 || X2<1 || Y<1)
		{
			return false;
		}

		if(X1>M_ || X2>M_ || Y>N_)
		{
			return false;
		}

		if(!C)
		{
			return false;
		}

		for(int X=min(X1,X2); X<=max(X1,X2); ++X)
		{
			bitMap_[Y-1][X-1] = C;
		}

		return true;

	}

	bool DrawFilledRectangle()
	{
		int X1 = -1;
		int Y1 = -1;
		int X2 = -1;
		int Y2 = -1;
		char C = 0;

		buffer_ >> X1;
		buffer_ >> Y1;
		buffer_ >> X2;
		buffer_ >> Y2;
		buffer_ >> C;

		if(X1<1 || X2<1 || Y1<1 || Y2<1)
		{
			return false;
		}

		if(X1>M_ || X2>M_ || Y1>N_|| Y2>N_)
		{
			return false;
		}

		if(!C)
		{
			return false;
		}

		for(int X=min(X1,X2); X<=max(X1,X2); ++X)
		{
			for(int Y=min(Y1,Y2); Y<=max(Y1,Y2); ++Y)
			{
				bitMap_[Y-1][X-1] = C;
			}
		}

		return true;
	}

	bool FillRegion()
	{
		int X = -1;
		int Y = -1;
		char C = 0;

		buffer_ >> X;
		buffer_ >> Y;
		buffer_ >> C;

		if(X<1 || Y<1)
		{
			return false;
		}

		if(X>M_ || Y>N_)
		{
			return false;
		}

		if(!C)
		{
			return false;
		}

		return FillRegion(X,Y,C);
	}

	bool FillRegion(int X,int Y,char C)
	{
		int P = bitMap_[Y-1][X-1];

		set< pair<int, int> > toFillPoints;

		stack< pair<int, int> > checkPoints;

		checkPoints.push(make_pair(Y,X));
		toFillPoints.insert(make_pair(Y,X));

		while(checkPoints.size())
		{
			pair<int, int> points = checkPoints.top();
			checkPoints.pop();

			int dx[] = { 0,  0, -1, +1};
			int dy[] = {-1, +1,  0,  0};

			for(int i = 0; i<4; ++i)
			{
				int Ys = points.first + dy[i];
				int Xs = points.second + dx[i];

				if(Xs<1 || Ys<1 )
				{
					continue;
				}

				if(Xs>M_ || Ys>N_)
				{
					continue;
				}

				if(bitMap_[Ys-1][Xs-1] == P && toFillPoints.find(make_pair(Ys,Xs)) == toFillPoints.end())
				{
					toFillPoints.insert(make_pair(Ys,Xs));
					checkPoints.push(make_pair(Ys,Xs));
				}
			}

		}

		set< pair<int, int> >::iterator iter = toFillPoints.begin();

		while(iter != toFillPoints.end())
		{
			int Ys = iter->first;
			int Xs = iter->second;

			bitMap_[Ys-1][Xs-1] = C;

			++iter;
		}

		return true;
	}

private:

	char command_;
	stringstream buffer_;

	vector<string> args_;

	vector< vector<char> > bitMap_;
	int M_;
	int N_;
};


int main()
{
	GraphicalEditor problem;

	problem.Solve();

	return 0;
}