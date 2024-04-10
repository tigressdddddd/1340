# include "gobang.h"
# include "stdlib.h"
# include <iostream>
using namespace std;



void DisplayBoard() 
{	
	//显示棋盘
	int i, j;
	char line;
	char ary;
	
	system("cls");   //清屏

	for(j = 0,line = 15; j <= SIZE - 1; j++)
	{
		printf("%2d",line);
		line -= 1;
		for(i = 0; i <= SIZE - 1; i++)
		{
			switch(Board[j][i])
			{
			case 1:
				cout <<"┏";
				break;
				
			case 2:
				printf("┓");
				break;
				
			case 3:
				printf("┛");
				break;
				
			case 4:
				printf("┗");
				break;
				
			case 5:
				printf("┠");
				break;
				
			case 6:
				printf("┯");
				break;
				
			case 7:
				printf("┨");
				break;
				
			case 8:
				printf("┷");
				break;
				
			case 9:
				printf("┼");
				break;
				
			case BLACKtem:      // 黑子上一步
				printf("▲");
				break;
				
			case WHITEtem:      //白子上一步
				printf("△");
				break;
				
			case BLACK:      //黑子通常
				printf("●");
				break;
				
			case WHITE:
				printf("○");  //白子通常
				break;
			}
			if(i == SIZE - 1)
			{
				printf("\n");
			}
			
		}
	}
	
	printf("   ");
	for (ary = 'A'; ary < 'A' + SIZE ; ary++)
		printf("%c ",ary);
	
	printf("\n");
}
//可以解释一下这个五子棋的代码吗
