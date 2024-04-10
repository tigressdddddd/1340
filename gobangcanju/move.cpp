# include <iostream>
# include "gobang.h"



void MoveP(int *pBoard, int piece)	// ������ 
{	
	char cY, c;
	int iX;
	int iValue; 
	
	// ��ȡ����λ�ò���������ʽ�Ƿ�Ϸ� 
	printf("Please enter the placement position (letters+numbers):");
	while((c = getchar()) != '\n');
	scanf("%c%d", &cY, &iX);
	
	if((cY >= 'A' && cY <= 'O') && (iX >= 1 && iX <= 15))
	{
		Posi[0] = 15 - iX;
		Posi[1] = cY - 'A';
	} 
	else 
	{
		printf("The input format is incorrect, please re-enter the location:");
		//getchar();
		MoveP(pBoard, piece);
		return; 
	}
	
	//������λ���Ƿ��������� 
	iValue = *(pBoard + 15 * Posi[0] + Posi[1]); 
	if(iValue == BLACK || iValue == WHITE || iValue == BLACKtem || iValue == WHITEtem)
	{
		printf("This position already has chess pieces, please re-enter the position:");
		MoveP(pBoard, piece);
		return;
	}	

	// ����
	*(pBoard + 15 * Posi[0] + Posi[1]) = piece;
} 


void MoveAi(int side)	// ai���� 
{
	int i, j;
	int x_b, y_b, x_w, y_w;
	int val_b = -1, val_w = -1;
	
	// Ѱ���������Ӹ��Ե���߷� 
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
	// ���ݷ�ֵ������������� 
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
