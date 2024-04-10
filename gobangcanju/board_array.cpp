# include <iostream>
# include "gobang.h"

int Board[SIZE][SIZE];       	// ���� 
int ScoreBoard_b[SIZE][SIZE];	// ���ӼƷְ� 
int ScoreBoard_w[SIZE][SIZE];	// ���ӼƷְ� 

int mode; 						//0Ϊ���˶�ս��1Ϊ�˻���ս 
int side_p, side_ai;			// ��¼ѡ����� 
int Posi[2];					// ��¼����λ�� 
int LineArray[9];				// ��¼��һ������������ 
int LineStateRecord[9];			// ��¼ĳһλ�ÿ����γɵ����ͣ�������Ӧ�����ͣ����꣩ 



void InitBoardArray()
{
	int i, j, k; 
	
	//��ʼ��Board 
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
	
	//��ʼ��ScoreBoard 
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

