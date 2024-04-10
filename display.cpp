# include "gobang.h"
# include "stdlib.h"
# include <iostream>
using namespace std;



void DisplayBoard() 
{	
	//show the chessboard
	int i, j;
	char line;
	char ary;
	
	system("cls");   //clear screen

	for(j = 0,line = 15; j <= SIZE - 1; j++)
	{
		cout << line << " ";
		line -= 1;
		for(i = 0; i <= SIZE - 1; i++)
		{
			switch(Board[j][i])
			{
			case 1:
				cout <<"┏";
				break;
				
			case 2:
				cout << "┓";
				break;
				
			case 3:
				cout << "┛";
				break;
				
			case 4:
				cout << "┗";
				break;
				
			case 5:
				cout << "┠";
				break;
				
			case 6:
				cout << "┯";
				break;
				
			case 7:
				cout << "┨";
				break;
				
			case 8:
				cout << "┷";
				break;
				
			case 9:
				cout << "┼";
				break;
				
			case BLACKtem:      //black chess; last step
				cout << "▲";
				break;
				
			case WHITEtem:      //white chess; last step
				cout << "△";
				break;
				
			case BLACK:      //black chess, current
				cout << "●";
				break;
				
			case WHITE:
				cout << "○";  //white chess, current
				break;
			}
			if(i == SIZE - 1)
			{
				cout << "\n";
			}
			
		}
	}
	
	cout << "   ";
	for (ary = 'A'; ary < 'A' + SIZE ; ary++)
		cout << ary << " ";
	
	cout << endl;
}
