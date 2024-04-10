# include "gobang.h"
# include "stdlib.h"
# include <iostream>
using namespace std;



void DisplayBoard() 
{	
	//��ʾ����
	int i, j;
	char line;
	char ary;
	
	system("cls");   //����

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
				
			case BLACKtem:      // ������һ��
				printf("▲");
				break;
				
			case WHITEtem:      //������һ��
				printf("△");
				break;
				
			case BLACK:      //����ͨ��
				printf("●");
				break;
				
			case WHITE:
				printf("○");  //����ͨ��
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
//���Խ���һ�����������Ĵ�����
