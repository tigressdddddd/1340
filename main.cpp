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
	
	if(mode) // 人机对战 
	{
		// initial 
		InitBoardArray();
		DisplayBoard();
		
		ChooseSide();
		
		while(side_p == BLACK)
		{	
			//黑子落子 
			ChangeTemPieces(BLACKtem);		// 改变tem棋子 
			MoveP(&Board[0][0], BLACKtem);	// 落子 
			x = Posi[0];					// 记录落子位置 
			y = Posi[1];
			if(judge(x, y) == -1)			// 禁手判定 
			{
				printf("禁手！");
				break;   
			}
			ChangeScoreBoard(x, y, Board);	// 更新计分板 
			DisplayBoard();					// 打印棋盘 
			if(judge(x, y) == BLACK)		// 胜利判定 
			{
				printf("黑子获胜！");
				break; 
			}
			//白子落子 
			ChangeTemPieces(WHITEtem);
			MoveAi(WHITEtem);
			x = Posi[0];
			y = Posi[1];
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
			printf("落子于%c%d.\n", y + 'A', 15 - x);
			if(judge(x, y) == WHITE)
			{
				printf("白子获胜！");
				break; 
			}
		}
		
		while(side_p == WHITE)
		{
			//黑子落子 
			ChangeTemPieces(BLACKtem);
			MoveAi(BLACKtem);
			x = Posi[0];
			y = Posi[1];
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
	
			printf("落子于%c%d.\n", y + 'A', 15 - x); 
			if(judge(x, y) == BLACK)
			{
				printf("黑子获胜！");
				break; 
			}
			//白子落子 
			ChangeTemPieces(WHITEtem);
			MoveP(&Board[0][0], WHITEtem);
			x = Posi[0];
			y = Posi[1]; 
			ChangeScoreBoard(x, y, Board);
			DisplayBoard();
			if(judge(x, y) == WHITE)
			{
				printf("白子获胜！");
				break; 
			}
		}	
	}
	
	else // 人人对战 
	{
		int i;
		
		InitBoardArray();
		DisplayBoard();
		
		while(1)
		{
			// 黑子落子 
			ChangeTemPieces(BLACKtem);
			MoveP(&Board[0][0], BLACKtem);
			x = Posi[0];
			y = Posi[1];
			if(judge(x, y) == -1)
			{
				printf("禁手！");
				break;   
			}
			ChangeScoreBoard(x, y, Board);
			DisplayBoard();
			if(judge(x, y) == BLACK)
			{
				printf("黑子获胜！");
				break; 
			}
			
			//白子落子 
			ChangeTemPieces(WHITEtem);
			MoveP(&Board[0][0], WHITEtem);
			ChangeScoreBoard(Posi[0], Posi[1], Board);
			DisplayBoard();
			if(judge(x, y) == WHITE)
			{
				printf("白子获胜！");
				break; 
			}	
		}		
	}
	
	while(1) //防止直接退出 
	{	
		x = getchar(); 
		if(x == '0') break;
	}  
}

