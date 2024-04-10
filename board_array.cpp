# include <iostream>
# include "gobang.h"

int Board[SIZE][SIZE];       	// chessboard
int ScoreBoard_b[SIZE][SIZE];	// the scoreboard of black chess   
int ScoreBoard_w[SIZE][SIZE];	// the scoreboard of white chess

int mode; 						//mode 0: man vs man, mode 1: man vs machine 
int side_p, side_ai;			// record which side you choose 
int Posi[2];					// record the place where you drop the chess piece
int LineArray[9];				// record the dropping chess of a single side 
int LineStateRecord[9];			// Records possible moves in a position, with indexes corresponding to moves (see macro) 



void InitBoardArray()
{
	int i, j, k; 
	
	//Initialize Board 
	Board[0][0] = 1;
	Board[0][SIZE - 1] = 2;
	Board[SIZE - 1][SIZE - 1] = 3;
	Board[SIZE - 1][0] = 4;
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][0] = 5;
	}
	
	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[0][i] = 6;
	}
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][SIZE - 1] = 7;
	}
	
	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[SIZE - 1][i] = 8;
	}
	
	for (j = 1; j <= SIZE - 2; j++)
	{
		for (i = 1; i <= SIZE - 2; i++)
		{
			Board[j][i] = 9;
		}
	}
	
	//Initialize ScoreBoard 
	for(k = 0; k <= (SIZE + 1) / 2; k++)
		for(i = k; i < SIZE - k; i++)
			for(j = k; j < SIZE - k; j++)
				if(i == k || j == k || i == SIZE - k - 1 || j == SIZE - k -1)
				{
					ScoreBoard_b[i][j] = k;
					ScoreBoard_w[i][j] = k;
				}
	
}


void PrintBoardArray(int *pBoard)
{
	int i;
	
	cout << endl;
	for(i = 0; i < SIZE * SIZE; i++)
	{
		cout << *(pBoard + i) << "\t";
		if(i % 15 == 14) cout << endl;
	}
}


void ChangeTemPieces(int piece)
{
	int i, j;
	for(i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			if(Board[i][j] == piece) Board[i][j] = (piece == BLACKtem) ? BLACK : WHITE;
} 

