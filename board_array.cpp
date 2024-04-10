# include <iostream>
# include "gobang.h"

int Board[SIZE][SIZE];       	// 棋盘 
int ScoreBoard_b[SIZE][SIZE];	// 黑子计分板 
int ScoreBoard_w[SIZE][SIZE];	// 白子计分板 

int mode; 						//0为人人对战，1为人机对战 
int side_p, side_ai;			// 记录选边情况 
int Posi[2];					// 记录落子位置 
int LineArray[9];				// 记录单一方向的落子情况 
int LineStateRecord[9];			// 记录某一位置可能形成的棋型，索引对应着棋型（见宏） 



void InitBoardArray()
{
	int i, j, k; 
	
	//初始化Board 
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
	
	//初始化ScoreBoard 
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
	
	printf("\n");
	for(i = 0; i < SIZE * SIZE; i++)
	{
		printf("%d\t", *(pBoard + i));
		if(i % 15 == 14) printf("\n");
	}
}


void ChangeTemPieces(int piece)
{
	int i, j;
	for(i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
			if(Board[i][j] == piece) Board[i][j] = (piece == BLACKtem) ? BLACK : WHITE;
} 

