/*
Check the Check




Your task is to write a program that reads a chessboard configuration and identifies whether a king is under attack (in check). A king is in check if it is on square which can be taken by the opponent on his next move.

White pieces will be represented by uppercase letters, and black pieces by lowercase letters. The white side will always be on the bottom of the board, with the black side always on the top.

For those unfamiliar with chess, here are the movements of each piece:

Pawn (p or P):
can only move straight ahead, one square at a time. However, it takes pieces diagonally, and that is what concerns you in this problem.

Knight (n or N)
: has an L-shaped movement shown below. It is the only piece that can jump over other pieces.

Bishop (b or B)
: can move any number of squares diagonally, either forward or backward.

Rook (r or R)
: can move any number of squares vertically or horizontally, either forward or backward.

Queen (q or Q)
: can move any number of squares in any direction (diagonally, horizontally, or vertically) either forward or backward.

King (k or K)
: can move one square at a time in any direction (diagonally, horizontally, or vertically) either forward or backward. 

Movement examples are shown below, where ``*'' indicates the positions where the piece can capture another piece:

Pawn          Rook          Bishop        Queen         King          Knight
........      ...*....      .......*      ...*...*      ........      ........
........      ...*....      *.....*.      *..*..*.      ........      ........
........      ...*....      .*...*..      .*.*.*..      ........      ..*.*...
........      ...*....      ..*.*...      ..***...      ..***...      .*...*..
...p....      ***r****      ...b....      ***q****      ..*k*...      ...n....
..*.*...      ...*....      ..*.*...      ..***...      ..***...      .*...*..
........      ...*....      .*...*..      .*.*.*..      ........      ..*.*...
........      ...*....      *.....*.      *..*..*.      ........      ........

Remember that the knight is the only piece that can jump over other pieces. The pawn movement will depend on its side. If it is a black pawn, it can only move one square diagonally down the board. If it is a white pawn, it can only move one square diagonally up the board. The example above is a black pawn, described by a lowercase ``p''. We use ``move" to indicate the squares where the pawn can capture another piece.

Input

There will be an arbitrary number of board configurations in the input, each consisting of eight lines of eight characters each. A ``.'' denotes an empty square, while upper- and lowercase letters represent the pieces as defined above. There will be no invalid characters and no configurations where both kings are in check. You must read until you find an empty board consisting only of ``.'' characters, which should not be processed. There will be an empty line between each pair of board configurations. All boards, except for the empty one, will contain exactly one white king and one black king.

Output

For each board configuration read you must output one of the following answers:

Game #d: white king is in check.

Game #d: black king is in check.

Game #d: no king is in check.

where d stands for the game number starting from 1.

Sample Input

..k.....
ppp.pppp
........
.R...B..
........
........
PPPPPPPP
K.......

rnbqk.nr
ppp..ppp
....p...
...p....
.bPP....
.....N..
PP..PPPP
RNBQKB.R

........
........
........
........
........
........
........
........

Sample Output

Game #1: black king is in check.
Game #2: white king is in check.


*/

#include <string>
#include <iostream>
#include <vector>
using namespace std;

enum PieceType
{
	White,
	Black
};

struct Position
{
	int x;
	int y;

	Position() : x(-1), y(-1) {}

	Position(int xv, int yv) : x(xv), y(yv) {}

	Position(const Position& pos) : x(pos.x), y(pos.y) {}

	Position& operator=(const Position& pos)
	{
		x = pos.x;
		y = pos.y;
		return *this;
	}

	Position operator+(const Position& pos)
	{
		Position p(*this);

		p.x+=pos.x;
		p.y+=pos.y;

		return p;
	}

	Position& operator+=(const Position& pos)
	{
		x+=pos.x;
		y+=pos.y;

		return *this;
	}

	bool IsInside() const 
	{
		return (x>=0 && x<=7) && (y>=0 &&y<=7);
	}

	bool IsSentinel()
	{
		return (x==-1 && y==-1);
	}

	bool operator==(const Position& pos)
	{
		return (x==pos.x && y==pos.y);
	}

	void Clear()
	{
		x = -1;
		y = -1;
	}

};

struct Cell;
class Piece;
typedef Piece* PiecePtr;

struct Cell
{
	Position pos;
	PiecePtr piece;

	Cell() : piece(NULL) {}

	~Cell();

	void Clear();

	void MakeNoPiece(int x, int y)
	{
		pos = Position(x,y);
		piece = NULL;
	}

	template < typename P>
	void MakePiece(Cell (*board)[8], int x, int y, PieceType type) 
	{
		pos = Position(x,y);

		if(piece)
		{
			delete piece;
		}

		piece =  new P(board, pos, type);
	}
};

class Piece
{

public: 
	Piece(Cell (*board)[8], const Position& pos, PieceType type) : board_(board), currPos_(pos), type_(type)
	{
	}

	virtual ~Piece() {}

	Position NextMove()
	{
		if(iter_ == moves_.end()) return Position();
		Position ret = *iter_;
		++iter_;
		return ret;
	}

	void GenerateMoves()
	{
		moves_.clear();

		for(size_t i=0; i<dx_.size(); ++i)
		{
			for(int m=1; m<=range_; ++m)
			{
				Position n = currPos_ + Position(dx_[i]*m , dy_[i]*m);

				if(n.IsInside())
				{
					if(board_[n.x][n.y].piece == NULL)
					{
						moves_.push_back(n);
						continue;
					}
					else if(board_[n.x][n.y].piece->Type() != type_)
					{
						moves_.push_back(n);
						break;
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
		}

		iter_ = moves_.begin();
	}

	PieceType Type()
	{
		return type_;
	}

private:
	Position currPos_;
	PieceType type_;
	vector<Position> moves_;
	vector<Position>::iterator iter_;
	Cell (*board_)[8];

protected:
	vector<int> dx_;
	vector<int> dy_;
	int range_;
};

Cell::~Cell()
{
	Clear();
}

void Cell::Clear()
{
	pos.Clear();
	delete  piece;
	piece = NULL;
}


class King : public Piece
{
public:
	King(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {-1, -1, -1, +0, +0, +1, +1, +1};
		int dy[] = {-1, +0, +1, -1, +1, -1, +0, +1};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 1;
	}
};

class Queen : public Piece
{
public:
	Queen(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {-1, -1, -1, +0, +0, +1, +1, +1};
		int dy[] = {-1, +0, +1, -1, +1, -1, +0, +1};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 8;
	}
};

class Bishop : public Piece
{
public:
	Bishop(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {-1, -1, +1, +1};
		int dy[] = {-1, +1, -1, +1};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 8;
	}
};

class Knight : public Piece
{
public:
	Knight(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {-1, -1, +1, +1, -2, -2, +2, +2};
		int dy[] = {-2, +2, -2, +2, -1, +1, -1, +1};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 1;
	}
};

class Rook : public Piece
{
public:
	Rook(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {-1, +1, +0, +0};
		int dy[] = {+0, +0, -1, +1};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 8;
	}
};

class BlackPawn : public Piece
{
public:
	BlackPawn(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {+1, +1,};
		int dy[] = {-1, +1,};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 1;
	}
};

class WhitePawn : public Piece
{
public:
	WhitePawn(Cell (*board)[8], const Position& pos, PieceType type) : Piece(board,pos,type)
	{
		int dx[] = {-1, -1,};
		int dy[] = {-1, +1,};

		dx_ = vector<int>(dx, dx+sizeof(dx)/sizeof(int));
		dy_ = vector<int>(dy, dy+sizeof(dy)/sizeof(int));
		range_ = 1;
	}
};

class Board
{
public:
	Board() {}

	~Board()
	{
		Clear();
	}

	bool MakeBoard(const vector<string>& data)
	{
		Clear();

		if(data.size() !=8) return false;

		for(size_t x=0; x<data.size(); ++x)
		{
			if(data[x].size() !=8) return false;

			for(size_t y=0; y<data[x].size(); ++y)
			{
				MakeCell(x,y,data[x][y]);
			}
		}

		return true;
	}

	Position KingPosition(const PieceType& type)
	{
		if(type == White)
			return whiteKingPos_;
		else if(type == Black)
			return blackKingPos_;

		return Position();
	}

	vector<PiecePtr> OpponentPieces(const PieceType& type)
	{
		if(type == White)
			return blackPieces_;
		else if(type == Black)
			return whitePieces_;

		return vector<PiecePtr>();
	}

private:

	void Clear()
	{
		blackPieces_.clear();
		whitePieces_.clear();
		whiteKingPos_.Clear();
		blackKingPos_.Clear();

		for(size_t x=0; x<8; ++x)
		{
			for(size_t y=0; y<8; ++y)
			{
				board_[x][y].Clear();
			}
		}
	}

	void MakeCell(int x, int y, char c)
	{
		switch(c)
		{
		case '.':
			{
				board_[x][y].MakeNoPiece(x,y);
			}
			break;
		case 'p':
			{
				board_[x][y].MakePiece<BlackPawn>(board_, x,y,Black);
				blackPieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'k':
			{
				board_[x][y].MakePiece<King>(board_, x,y,Black);
				blackPieces_.push_back(board_[x][y].piece);
				blackKingPos_ = Position(x,y);
			}
			break;
		case 'q':
			{
				board_[x][y].MakePiece<Queen>(board_, x,y,Black);
				blackPieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'b':
			{
				board_[x][y].MakePiece<Bishop>(board_, x,y,Black);
				blackPieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'n':
			{
				board_[x][y].MakePiece<Knight>(board_, x,y,Black);
				blackPieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'r':
			{
				board_[x][y].MakePiece<Rook>(board_, x,y,Black);
				blackPieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'P':
			{
				board_[x][y].MakePiece<WhitePawn>(board_, x,y,White);
				whitePieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'K':
			{
				board_[x][y].MakePiece<King>(board_, x,y,White);
				whitePieces_.push_back(board_[x][y].piece);
				whiteKingPos_ = Position(x,y);
			}
			break;
		case 'Q':
			{
				board_[x][y].MakePiece<Queen>(board_, x,y,White);
				whitePieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'B':
			{
				board_[x][y].MakePiece<Bishop>(board_, x,y,White);
				whitePieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'N':
			{
				board_[x][y].MakePiece<Knight>(board_, x,y,White);
				whitePieces_.push_back(board_[x][y].piece);
			}
			break;
		case 'R':
			{
				board_[x][y].MakePiece<Rook>(board_, x,y,White);
				whitePieces_.push_back(board_[x][y].piece);
			}
			break;
		}
	}

private:
	vector<PiecePtr> blackPieces_;
	vector<PiecePtr> whitePieces_;
	Position whiteKingPos_;
	Position blackKingPos_;
	Cell board_[8][8];
};

class ChessGame
{
public:
	template<typename T>
	bool IsKingInCheck(const T& king)
	{
		Position kingPos = board_.KingPosition(king);

		vector<PiecePtr> pieces = board_.OpponentPieces(king);

		for(size_t i = 0; i<pieces.size(); ++i)
		{
			PiecePtr piece = pieces[i];

			piece->GenerateMoves();

			Position next = piece->NextMove();

			while(!next.IsSentinel())
			{
				if(next == kingPos) return true;
				next = piece->NextMove();
			}
		}

		return false;
	}

	bool IsWhiteKingInCheck()
	{
		return IsKingInCheck(White);
	}

	bool IsBlackKingInCheck()
	{
		return IsKingInCheck(Black);
	}

	bool MakeBoard(const vector<string>& data)
	{
		return board_.MakeBoard(data);
	}

private:
	Board board_;
};

class ChessChecker
{
public:

	ChessChecker() : 
		gameNumber_(0)
	{
	}

	void Solve()
	{
		while(BuildBoard())
		{
			CheckWhoIsInCheck();
			PrintOutput();
		}
	}

private:

	void CheckWhoIsInCheck()
	{
		checkedKing_ = "no";

		if(game_.IsBlackKingInCheck())
		{
			checkedKing_ = "black";
		}
		else if(game_.IsWhiteKingInCheck())
		{
			checkedKing_ = "white";
		}
	}

	bool BuildBoard()
	{
		if(ReadInput())
		{
			return game_.MakeBoard(inputData_);
		}

		return false;
	}

	bool ReadInput()
	{
		inputData_.clear();

		bool allEmpty = true;

		for(int x=0; x<8; ++x)
		{
			string str;
			getline(cin, str);

			if(cin.bad() || !str.size())
			{
				return false;
			}

			if(str != "........")
			{
				allEmpty = false;
			}

			inputData_.push_back(str);
		}

		if(allEmpty)
		{
			return false;
		}

		string str;
		getline(cin, str);
		++gameNumber_;

		return true;
	}

	void PrintOutput()
	{
		std::cout<<"Game #"<<gameNumber_<<": "<<checkedKing_<<" king is in check."<<endl;
	}

	enum Checked
	{
		White,
		Black,
		None
	};

	vector<string> inputData_;
	ChessGame game_;
	size_t gameNumber_;
	string checkedKing_;
};

int main()
{
	ChessChecker problem;

	problem.Solve();

	return 0;
}