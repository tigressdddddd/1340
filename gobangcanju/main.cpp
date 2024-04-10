#define _CRT_SECURE_NO_WARNINGS
# include <cstdio>
# include <iostream>
# include "gobang.h"
#include "string"
# include <cstdlib>


int main()
{	
	int x, y;
	
	ChooseMode();
	
	if(mode==1) // �˻���ս 
	{
		// initial 
		InitBoardArray();
		DisplayBoard();
		
		ChooseSide();
		
		while(side_p == BLACK)
		{	
			//�������� 
			ChangeTemPieces(BLACKtem);		// �ı�tem���� 
			MoveP(&Board[0][0], BLACKtem);	// ���� 
			x = Posi[0];					// ��¼����λ�� 
			y = Posi[1];
			if(judge(x, y) == -1)			// �����ж� 
			{
				printf("Prohibition of Hands!");
				break;   
			}
			ChangeScoreBoard(x, y, Board);	// ���¼Ʒְ� 
			DisplayBoard();					// ��ӡ���� 
			if(judge(x, y) == BLACK)		// ʤ���ж� 
			{
				printf("Black wins!");
				break; 
			}
			//�������� 
			ChangeTemPieces(WHITEtem);
			MoveAi(WHITEtem);
			x = Posi[0];
			y = Posi[1];
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
			printf("placing pieces%c%d.\n", y + 'A', 15 - x);
			if(judge(x, y) == WHITE)
			{
				printf("White wins!");
				break; 
			}
		}
		
		while(side_p == WHITE)
		{
			//�������� 
			ChangeTemPieces(BLACKtem);
			MoveAi(BLACKtem);
			x = Posi[0];
			y = Posi[1];
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
	
			printf("placing pieces%c%d.\n", y + 'A', 15 - x); 
			if(judge(x, y) == BLACK)
			{
				printf("Black wins!");
				break; 
			}
			//�������� 
			ChangeTemPieces(WHITEtem);
			MoveP(&Board[0][0], WHITEtem);
			x = Posi[0];
			y = Posi[1]; 
			ChangeScoreBoard(x, y, Board);
			DisplayBoard();
			if(judge(x, y) == WHITE)
			{
				printf("White wins!");
				break; 
			}
		}	
	}
	
	if(mode==0) // ���˶�ս 
	{
		int i;
		
		InitBoardArray();
		DisplayBoard();
		
		while(1)
		{
			// �������� 
			ChangeTemPieces(BLACKtem);
			MoveP(&Board[0][0], BLACKtem);
			x = Posi[0];
			y = Posi[1];
			if(judge(x, y) == -1)
			{
				printf("Prohibition of Hands!");
				break;   
			}
			ChangeScoreBoard(x, y, Board);
			DisplayBoard();
			if(judge(x, y) == BLACK)
			{
				printf("Black wins!");
				break; 
			}
			
			//�������� 
			ChangeTemPieces(WHITEtem);
			MoveP(&Board[0][0], WHITEtem);
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
			if(judge(x, y) == WHITE)
			{
				printf("White wins!");
				break; 
			}	
		}		
	}
	if (mode==2){
		int i;
		
		InitBoardArray();
		chooseboard();
		DisplayBoard();
		
		while(1)
		{
			// 锟斤拷锟斤拷锟斤拷锟斤拷 
			ChangeTemPieces(BLACKtem);
			MoveP(&Board[0][0], BLACKtem);
			x = Posi[0];
			y = Posi[1];
			if(judge(x, y) == -1)
			{
				printf("Prohibition of Hands!");
				break;   
			}
			
			ChangeScoreBoard(x, y, Board);
			cout<<'1'<<endl;
			DisplayBoard();
			if(judge(x, y) == BLACK)
			{
				printf("Black wins!");
				break; 
			}
			
			//锟斤拷锟斤拷锟斤拷锟斤拷 
			ChangeTemPieces(WHITEtem);
			MoveP(&Board[0][0], WHITEtem);
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
			if(judge(x, y) == WHITE)
			{
				printf("White wins!");
				break; 
			}	
		}		

	}
	while(1) //��ֱֹ���˳� 
	{	
		x = getchar(); 
		if(x == '0') break;
	}  
}

