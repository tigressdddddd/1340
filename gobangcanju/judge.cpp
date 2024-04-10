# include "gobang.h"
# include <iostream>


int judge(int x, int y) 
{	

	int i, a, b;
	int type;
	
	//ȷ�����ӵ�һ�� 
	if(Board[x][y] == BLACKtem)
	{
		type = BLACK;
		if(RestrictedMove(x, y)) return -1;	//�����ж� 
	} 
	else type = WHITE;
	
	
	//��
	for(i=1, a=0; ; i++, a++)
		if(x-i < 0 || Board[x-i][y] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(x+i > 14 || Board[x+i][y] != type) break;
	if(a+b >= 4) return type;
	//�� 
	for(i=1, a=0; ; i++, a++)
		if(y-i < 0 || Board[x][y-i] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(y+i > 14 || Board[x][y+i] != type) break;
	if(a+b >= 4) return type;
	//����-����
	for(i=1, a=0; ; i++, a++)
		if(x-i < 0 || y-i < 0 || Board[x-i][y-i] != type) break;
	for(i=1, b=0; ; i++, b++)
		if(x+i > 14 || y+i > 14 || Board[x+i][y+i] != type) break;
	if(a+b >= 4) return type;
	//����-����
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
	printf("Please select the mode for\"pvp\"(p)or\"pve\"(a) or Residual situation(r):");
	scanf("%s", &s);
	if(s[0] == 'p')
		mode = 0;
	else if(s[0] == 'a')
		mode = 1;
	else if(s[0] == 'r')
		mode = 2;
	else
	{
		printf("\nPlease enter letters: p or a.");
		ChooseMode();
	}
} 


void ChooseSide()
{	
	char s[2];
	printf("Please choose the first black box (b) or the second white box (w):");
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
		printf("\nPlease enter the letters b or w.");
		ChooseSide();
	}
}


int RestrictedMove(int x, int y)	//�ж��Ƿ�Ϊ����
{	
	if(ScoreBoard_b[x][y] == -2) return 1;
	else return 0;
}
