#include <stdio.h>

// Oversize the board so that the knights don't index out of bounds when they search for the king
// along the edge. This is similar to the minesweeper algorithm and a few others.
char board[12][12];

int ReadBoard();
int ScanRowForPieces(char* row);

// Helpers for converting piece colors to target king.
char KingFromPieceColor(unsigned char pieceColor);
char NextPieceFromVector(unsigned long boardRow, unsigned long boardCol, int vecX, int vecY);

// Methods for playing the board and then as pieces are found playing each piece
int PlayBoard();
int PlayPawn(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol);
int PlayRook(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol);
int PlayBishop(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol);
int PlayKnight(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol);
int PlayQueen(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol);

int main()
{
	unsigned long game = 0;
	while(ReadBoard())
	{
		const char* szLoser = "no";
		int winner = 0;

		game++;
		winner = PlayBoard();
		switch (winner)
		{
			case 1: szLoser = "white"; break;
			case 2: szLoser = "black"; break;
		}
		printf("Game #%d: %s king is in check.\n", game, szLoser);
	}
}

int ReadBoard()
{
	char extraLine[1024];
	unsigned long boardRow = 0;
	int fSeenPlayer = 0;

	// Initialize the entire board to NUL characters since these won't be
	// valid board spots like '.' nor will they match a king like 'K' or 'k'.
	memset(board, '\0', sizeof(board));
	for (boardRow = 2; boardRow <= 9; boardRow++)
	{
		char* row = gets(&board[boardRow][2]);
		if (fSeenPlayer == 0)
		{
			fSeenPlayer = ScanRowForPieces(row);
		}
#ifdef DEBUG
		printf("%s\n", row);
#endif
	}
	gets(extraLine);
	return fSeenPlayer;
}

int ScanRowForPieces(char* row)
{
	while (*row == '.')
	{
		row++;
	}
	if (*row == '\0')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int PlayBoard()
{
	unsigned long boardRow = 1;
	unsigned long boardCol = 1;

	for (boardRow = 2; boardRow <= 9; boardRow++)
	{
		for (boardCol = 2; boardCol <= 9; boardCol++)
		{
			unsigned char fCheck = 0;
			unsigned char pieceColor = 0;
			char piece = board[boardRow][boardCol];
			switch (piece)
			{
				case 'p':
				case 'n':
				case 'b':
				case 'r':
				case 'q':
				case 'k':
					pieceColor = 1;
					break;

				case 'P':
				case 'N':
				case 'B':
				case 'R':
				case 'Q':
				case 'K':
					pieceColor = 2;
					break;
			}

			switch (piece)
			{
				case 'p': case 'P': fCheck = PlayPawn(pieceColor, boardRow, boardCol); break;
				case 'n': case 'N': fCheck = PlayKnight(pieceColor, boardRow, boardCol); break;
				case 'b': case 'B': fCheck = PlayBishop(pieceColor, boardRow, boardCol); break;
				case 'r': case 'R': fCheck = PlayRook(pieceColor, boardRow, boardCol); break;
				case 'q': case 'Q': fCheck = PlayQueen(pieceColor, boardRow, boardCol); break;
				// Kings can't be attacking each other, or they'd both be in check, against the rules.
			}

			if (fCheck)
			{
				return pieceColor;
			}
		}
	}
	return 0;
}

char KingFromPieceColor(unsigned char pieceColor)
{
	return (pieceColor == 1) ? 'K' : 'k';;
}
char NextPieceFromVector(unsigned long boardRow, unsigned long boardCol, int vecX, int vecY)
{
	do
	{
		boardRow += vecY;
		boardCol += vecX;
	}
	while (board[boardRow][boardCol] == '.');

	return board[boardRow][boardCol];
}

int PlayPawn(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol)
{
	int dir = (pieceColor == 1) ? 1 : -1;
	char targetKing = KingFromPieceColor(pieceColor);
	char king1 = board[boardRow + dir][boardCol + 1];
	char king2 = board[boardRow + dir][boardCol - 1];

	if (king1 == targetKing || king2 == targetKing)
	{
#ifdef DEBUG
		printf("Pawn check %lu, %lu\n", boardRow, boardCol);
#endif
		return pieceColor;
	}
	return 0;
}

int PlayRook(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol)
{
	char targetKing = KingFromPieceColor(pieceColor);
	char king1 = NextPieceFromVector(boardRow, boardCol, -1, 0);
	char king2 = NextPieceFromVector(boardRow, boardCol, 1, 0);
	char king3 = NextPieceFromVector(boardRow, boardCol, 0, -1);
	char king4 = NextPieceFromVector(boardRow, boardCol, 0, 1);

	if (king1 == targetKing || king2 == targetKing || king3 == targetKing || king4 == targetKing)
	{
#ifdef DEBUG
		printf("Rook check %lu, %lu\n", boardRow, boardCol);
#endif
		return pieceColor;
	}
	return 0;
}

int PlayBishop(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol)
{
	char targetKing = KingFromPieceColor(pieceColor);
	char king1 = NextPieceFromVector(boardRow, boardCol, -1, -1);
	char king2 = NextPieceFromVector(boardRow, boardCol, -1, 1);
	char king3 = NextPieceFromVector(boardRow, boardCol, 1, 1);
	char king4 = NextPieceFromVector(boardRow, boardCol, 1, -1);

	if (king1 == targetKing || king2 == targetKing || king3 == targetKing || king4 == targetKing)
	{
#ifdef DEBUG
		printf("Bishop check %lu, %lu\n", boardRow, boardCol);
#endif
		return pieceColor;
	}
	return 0;
}

int PlayQueen(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol)
{
	int winner = PlayBishop(pieceColor, boardRow, boardCol);
	if (winner == 0)
	{
		winner = PlayRook(pieceColor, boardRow, boardCol);
	}
	return winner;
}

int PlayKnight(unsigned char pieceColor, unsigned long boardRow, unsigned long boardCol)
{
	char targetKing = KingFromPieceColor(pieceColor);
	char king1 = board[boardRow-1][boardCol-2];
	char king2 = board[boardRow-2][boardCol-1];
	char king3 = board[boardRow-1][boardCol+2];
	char king4 = board[boardRow-2][boardCol+1];

	char king5 = board[boardRow+1][boardCol-2];
	char king6 = board[boardRow+2][boardCol-1];
	char king7 = board[boardRow+1][boardCol+2];
	char king8 = board[boardRow+2][boardCol+1];

	if (king1 == targetKing || king2 == targetKing || king3 == targetKing || king4 == targetKing ||
	    king5 == targetKing || king6 == targetKing || king7 == targetKing || king8 == targetKing)
	{
		return pieceColor;
	}
	return 0;
}
