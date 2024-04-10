# include <iostream>
# include "gobang.h"



void MoveP(int *pBoard, int piece)	// 人落子 
{	
	char cY, c;
	int iX;
	int iValue; 
	
	// 获取落子位置并检查输入格式是否合法 
	printf("请输入落子位置(字母+数字):");
	while((c = getchar()) != '\n');
	scanf("%c%d", &cY, &iX);
	
	if((cY >= 'A' && cY <= 'O') && (iX >= 1 && iX <= 15))
	{
		Posi[0] = 15 - iX;
		Posi[1] = cY - 'A';
	} 
	else 
	{
		printf("输入格式有误，请重新输入位置：");
		getchar();
		MoveP(pBoard, piece);
		return; 
	}
	
	//检查这个位置是否已有棋子 
	iValue = *(pBoard + 15 * Posi[0] + Posi[1]); 
	if(iValue == BLACK || iValue == WHITE || iValue == BLACKtem || iValue == WHITEtem)
	{
		printf("这个位置已经有棋子，请重新输入位置：");
		MoveP(pBoard, piece);
		return;
	}	

	// 落子
	*(pBoard + 15 * Posi[0] + Posi[1]) = piece;
} 


void MoveAi(int side)	// ai落子 
{
	int i, j;
	int x_b, y_b, x_w, y_w;
	int val_b = -1, val_w = -1;
	
	// 寻找两种棋子各自的最高分 
	for(i = 0; i < 15; i++)
		for(j = 0; j < 15; j++)
		{
			if(ScoreBoard_b[i][j] > val_b)
			{
				val_b = ScoreBoard_b[i][j];
				x_b = i;
				y_b = j;
			}
			if(ScoreBoard_w[i][j] > val_w) 
			{
				val_w = ScoreBoard_w[i][j];
				x_w = i;
				y_w = j;
			}
		}
	// 根据分值决定进攻或防守 
	if(val_b >= val_w)
	{
		for(i = 0; i < 15; i++)
		{
			for(j = 0; j < 15; j++)
			{
				if(ScoreBoard_b[i][j] == val_b)
				{
					if(ScoreBoard_w[i][j] > ScoreBoard_w[x_b][y_b])
					{
						x_b = i;
						y_b = j;
					}
				}
			}
		}
		Board[x_b][y_b] = side;
		Posi[0] = x_b;
		Posi[1] = y_b; 
	}
	
	else
	{
		for(i = 0; i < 15; i++)
		{
			for(j = 0; j < 15; j++)
			{
				if(ScoreBoard_w[i][j] == val_w)
				{
					if(ScoreBoard_b[i][j] > ScoreBoard_b[x_w][y_w])
					{
						x_w = i;
						y_w = j;
					}
				}
			}
		}
		Board[x_w][y_w] = side;
		Posi[0] = x_w;
		Posi[1] = y_w;
	}
}
