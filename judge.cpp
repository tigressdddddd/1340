# include "gobang.h"
# include <iostream>


int judge(int x, int y) 
{	

	int i, a, b;
	int type;
	
	//确定落子的一方 
	if(Board[x][y] == BLACKtem)
	{
		type = BLACK;
		if(RestrictedMove(x, y)) return -1;	//禁手判定 
	} 
	else type = WHITE;
	
	
	//横
	for(i=1, a=0; ; i++, a++)
		if(x-i < 0 || Board[x-i][y] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(x+i > 14 || Board[x+i][y] != type) break;
	if(a+b >= 4) return type;
	//竖 
	for(i=1, a=0; ; i++, a++)
		if(y-i < 0 || Board[x][y-i] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(y+i > 14 || Board[x][y+i] != type) break;
	if(a+b >= 4) return type;
	//左上-右下
	for(i=1, a=0; ; i++, a++)
		if(x-i < 0 || y-i < 0 || Board[x-i][y-i] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(x+i > 14 || y+i > 14 || Board[x+i][y+i] != type) break;
	if(a+b >= 4) return type;
	//左下-右上
	for(i=1, a=0; ; i++, a++)
		if(x+i > 14 || y-i < 0 || Board[x+i][y-i] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(x-i < 0 || y+i > 14 || Board[x-i][y+i] != type) break;
	if(a+b >= 4) return type;

	return 0; 
} 


void ChooseMode()
{	
	char s[2];
	printf("请选择模式为\"人人对战\"(p)或\"人机对战\"(a):");
	scanf("%s", &s);
	if(s[0] == 'p')
		mode = 0;
	else if(s[0] == 'a')
		mode = 1;
	else
	{
		printf("\n请输入字母 p 或 a.");
		ChooseMode();
	}
} 


void ChooseSide()
{	
	char s[2];
	printf("请选择先手黑子(b)或后手白子(w):");
	scanf("%s", &s);
	if(s[0] == 'b')
	{
		side_p = BLACK;
		side_ai = WHITE;
	}
	else if(s[0] == 'w')
	{
		side_p = WHITE;
		side_ai = BLACK;
	} 
	else
	{
		printf("\n请输入字母 b 或 w.");
		ChooseSide();
	}
}


int RestrictedMove(int x, int y)	//判断是否为禁手
{	
	if(ScoreBoard_b[x][y] == -2) return 1;
	else return 0;
}
