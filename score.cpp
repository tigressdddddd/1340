# include <iostream>
# include "gobang.h"


void ChangeScoreBoard(int x, int y, int (*pBoard)[15])	// refresh score board 
{
	int i;
	
	//the positon to place the chess is -1 
	ScoreBoard_b[x][y] = -1;
	ScoreBoard_w[x][y] = -1;
	
	//Re-score total 64 values in 32 positions within 4 squares in 4 directions of 2 kinds of chess pieces
	//verticle
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || i == 4) continue;
		if(ScoreBoard_w[x-4+i][y] != -1)
		{
			ScorePosi(x-4+i, y, pBoard, BLACK);
			ScorePosi(x-4+i, y, pBoard, WHITE);
		}
	}
	
	//anti=diagonal
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || y+4-i < 0 || y+4-i > 14 || i == 4) continue;
		if(ScoreBoard_w[x-4+i][y+4-i] != -1)
		{
			ScorePosi(x-4+i, y+4-i, pBoard, BLACK);
			ScorePosi(x-4+i, y+4-i, pBoard, WHITE);
		}
	}
	
	//horizontal
	for(i=0; i<9; i++)
	{
		if(y+4-i < 0 || y+4-i > 14 || i == 4) continue;
		if(ScoreBoard_w[x][y+4-i] != -1)
		{	
			ScorePosi(x, y+4-i, pBoard, BLACK);
			ScorePosi(x, y+4-i, pBoard, WHITE);
		}
	}
	
	//diagonal 
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || y-4+i < 0 || y-4+i > 14 || i == 4) continue;
		if(ScoreBoard_w[x-4+i][y-4+i] != -1)
		{
			ScorePosi(x-4+i, y-4+i, pBoard, BLACK);
			ScorePosi(x-4+i, y-4+i, pBoard, WHITE);
		}
	}
}


void ScorePosi(int x, int y, int (*pBoard)[15], int side) // score particular position
{	
	int i, j, flag_b, flag_w;
	
	// Determines if the position is legal  
	if(ScoreBoard_b[x][y] == -1 || ScoreBoard_w[x][y] == -1) return;
	
	//Obtain the data of the adjacent board in 4 directions, use LineState to determine the pattern, and record the result in LineStateRecord 
        //horizontal
	for(i=0; i<=9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14) LineArray[i] = op(side);	// Any piece that goes beyond the boundaries of the board is considered an opposing piece
		else if(i == 4) LineArray[i] = side;			// Center position preset as own piece (actually there is no piece) 
		else
		{
			LineArray[i] = pBoard[15*(x-4+i)][y] ;
		}
	}
	LineStateRecord[LineState(LineArray)] += 1;
	
	//anti-diagonal
	for(i=0; i<=9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || y+4-i < 0 || y+4-i > 14) LineArray[i] = op(side);
		else if(i == 4) LineArray[i] = side;
		else
		{
			LineArray[i] = pBoard[x-4+i][y+4-i];
		}
	}
	LineStateRecord[LineState(LineArray)] += 1;
	
	//verticle
	for(i=0; i<=9; i++)
	{
		if(y+4-i < 0 || y+4-i > 14) LineArray[i] = op(side);
		else if(i == 4) LineArray[i] = side;
		else
		{
			LineArray[i] = pBoard[x][y+4-i];
		}
	}
	LineStateRecord[LineState(LineArray)] += 1;
	
	//diagonal 
	for(i=0; i<=9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || y-4+i < 0 || y-4+i > 14) LineArray[i] = op(side);
		else if(i == 4) LineArray[i] = side;
		else
		{
			LineArray[i] = pBoard[x-4+i][y-4+i];
		}
	}
	LineStateRecord[LineState(LineArray)] += 1;
	
	
	//According to the obtained chess type data, estimate the possible value
	int score = 0;
	if(side == BLACK || side == BLACKtem)
	{
		//a restricted move scores is -2
		if(LineStateRecord[CL] && !LineStateRecord[L5]) score = -2; 
		else if(LineStateRecord[L3] >= 2 && !LineStateRecord[L5]) score = -2;
		else if((LineStateRecord[L4] + LineStateRecord[S4] >= 2) && !LineStateRecord[L5]) score = -2;
		// stronger move has higher score, if same chess type, your own moves have higher score than the opponent's move, the opponent move thet does not have to defend has lower score
		else if(side_p == BLACK)
		{
			score += LineStateRecord[L5] * 400000;
			score += LineStateRecord[L4] * 200000;
			score += (LineStateRecord[S4] && LineStateRecord[L3]) * 200000;
			score += (LineStateRecord[S3] && LineStateRecord[L3]) * 5000;
			score += (LineStateRecord[L2] && LineStateRecord[L3]) * 4000;
			score += LineStateRecord[S4] * 800;
			score += LineStateRecord[L3] * 1800;
			score += LineStateRecord[L2] * 800;
			score += LineStateRecord[S3] * 100;
			score += LineStateRecord[S2] * 50;
			score += LineStateRecord[NTH] * 20;
		}
		else
		{
			score += LineStateRecord[L5] * 500000;
			score += LineStateRecord[L4] * 300000;
			score += (LineStateRecord[S4] && LineStateRecord[L3]) * 300000;
			score += (LineStateRecord[S3] && LineStateRecord[L3]) * 2000;
			score += (LineStateRecord[L2] && LineStateRecord[L3]) * 8000;
			score += LineStateRecord[S4] * 4000;
			score += LineStateRecord[L3] * 5000;
			score += LineStateRecord[L2] * 2500;
			score += LineStateRecord[S3] * 100;
			score += LineStateRecord[S2] * 50;
			score += LineStateRecord[NTH] * 20;
			// Adjacent pieces add or subtract points because we tend to choose lines over hops	
			flag_b = 0; flag_w = 0;
			for(i = x - 1; i <= x + 1; i++)
			{
				if(i < SIZE && i >= 0)
					for(j = y - 1; j <= y + 1; j++)
						if(j < SIZE && j >= 0)
						{
							if(Board[i][j] == BLACK || Board[i][j] == BLACKtem)
								flag_b = 1;
							if(Board[i][j] == WHITE || Board[i][j] == WHITEtem)
								flag_w = 1;
						}				
			}
			score += flag_b * 500 - flag_w * 500;
		}
		ScoreBoard_b[x][y] = score;
	} 
	
	if(side == WHITE || side == WHITEtem)
	{
		if(side_p == BLACK)
		{
			score += LineStateRecord[CL] * 500000;
			score += LineStateRecord[L5] * 500000;
			score += LineStateRecord[L4] * 300000;
			score += (LineStateRecord[S4] >= 2) * 300000;
			score += (LineStateRecord[S4] && LineStateRecord[L3]) * 300000;
			score += (LineStateRecord[L3] >= 2) * 100000;
			score += (LineStateRecord[S3] && LineStateRecord[L3]) * 3000;
			score += (LineStateRecord[L2] && LineStateRecord[L3]) * 8000;
			score += LineStateRecord[S4] * 3000;
			score += LineStateRecord[L3] * 4000;
			score += LineStateRecord[L2] * 2000;
			score += LineStateRecord[S3] * 100;
			score += LineStateRecord[S2] * 50;
			score += LineStateRecord[NTH] * 20;
			flag_b = 0; flag_w = 0;
			for(i = x - 1; i <= x + 1; i++)
			{
				if(i < SIZE && i >= 0)
					for(j = y - 1; j <= y + 1; j++)
						if(j < SIZE && j >= 0)
						{
							if(Board[i][j] == BLACK || Board[i][j] == BLACKtem)
								flag_b = 1;
							if(Board[i][j] == WHITE || Board[i][j] == WHITEtem)
								flag_w = 1;
						}				
			}
			score += flag_w * 500 - flag_b * 500;
		}
		else
		{
			score += LineStateRecord[CL] * 400000;
			score += LineStateRecord[L5] * 400000;
			score += LineStateRecord[L4] * 200000;
			score += (LineStateRecord[S4] >= 2) * 200000;
			score += (LineStateRecord[S4] && LineStateRecord[L3]) * 200000;
			score += (LineStateRecord[L3] >= 2) * 100000;
			score += (LineStateRecord[S3] && LineStateRecord[L3]) * 2000;
			score += (LineStateRecord[L2] && LineStateRecord[L3]) * 3000;
			score += LineStateRecord[S4] * 800;
			score += LineStateRecord[L3] * 1500;
			score += LineStateRecord[L2] * 800;
			score += LineStateRecord[S3] * 100;
			score += LineStateRecord[S2] * 50;
			score += LineStateRecord[NTH] * 20;
		}
		ScoreBoard_w[x][y] = score;
	} 
	
	// Clear the array that records chess patterns
	for(i = 0; i <= 8; i++)
	{
		LineStateRecord[i] = 0;
	}
}


int LineState(int *pLineArray) 						//Process the chess pattern into the desired form 
{	
	ChangeLine(pLineArray); // turn chesspiece into needed format
	
	int u = 8, l = 0, i, j, flag, side = *(pLineArray + 4);
	
	//u and l are the upper and lower bounds of the interval for judging (opponent's chess piece and continue empty spaces are the boundaries, no need to consider situations beyond the boundaries). 
        //opposite chess piece boundary
	for(i = 3; i >= 0; i--)
		if(*(pLineArray + i) == op(side))
		{
			l = i;
			break;
		}
	for(i = 5; i <= 8; i++)
		if(*(pLineArray + i) == op(side))
		{
			u = i;
			break;
		}
	//continue empty spaces boundary
	flag = 0;
	for(i = 3; i >= 0; i--)
	{
		if(*(pLineArray + i) == 0) 
		{	
			if(!flag) flag = 1;
			else
			{
				l = max(l, i);
				break;
			}
		}
	}
	flag = 0;
	for(i = 5; i <= 8; i++)
	{
		if(*(pLineArray + i) == 0) 
		{	
			if(!flag) flag = 1;
			else
			{
				u = min(u, i);
				break;
			} 
		}
	}

	//To determine the moves within the boundary, output the most powerful moves
	//from strong to weak 
	int cnt, cnt_max, sum;
	int flag_l, flag_u;
	
	flag_l = l; flag_u = u;
	cnt = 0; cnt_max = 0;

	for(i = l; i <= u; i++)		//Gets the maximum number of continuous pieces cnt_max 
	{
		if(*(pLineArray + i) == side) cnt += 1;
		else 
		{	
			if(i < 4) flag_l = i;
			else if(i > 4) flag_u = min(flag_u, i);
			cnt_max = max(cnt, cnt_max);
			cnt = 0;
		}
		cnt_max = max(cnt, cnt_max);
	}
	
	// oooooo
	if(cnt_max >= 6) return CL; 
	// ooooo
	if(cnt_max == 5) return L5;
	// -oooo-
	if(cnt_max == 4)		
	{
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == 0) return L4;	// Determine whether the chess type is alive or not according to the boundary
	}
	}
	// -ooo-
	if(cnt_max == 3)
	{
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == 0) return L3;
	}
	// xoooo-
	if(cnt_max == 4)
	{
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == op(side)) return S4;
	}
	// ooo-o & oo-oo
	if(u - l + 1 >= 5)	//Determine the jump type 
	{	
		for(i = l; i <= u - 4; i++)
		{
			if(*(pLineArray + i) == side) 
			{
				sum = 0;
				for(j = i; j <= i + 4; j++)
				{
					sum += *(pLineArray + j);
				}
				if(sum == 4 * side) return S4;
			}
		}
	}
	// -oo-o-
	if(u - l + 1 >= 6)
	{	
		for(i = l; i <= u - 5; i++)
		{
			if(*(pLineArray + i) == 0 && *(pLineArray + i + 5) == 0) 
			{
				sum = 0;
				for(j = i; j <= i + 5; j++)
				{
					sum += *(pLineArray + j);
				}
				if(sum == 3 * side) return L3;
			}
		}
	}
	// -oo-
	if(cnt_max == 2)
	{
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == 0) return L2;
	}
	if(cnt_max == 3)
	{
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == op(side)) return S3;
	}
	if(cnt_max == 2)
	{
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == op(side)) return S2;
	}
	
	return NTH;
}


void ChangeLine(int *pLineArray)	//process the chess pattern to desired form 
{
	int i;
	//modify tem，positions with no chess pieces are 0 
	for(i = 0; i < 9; i++)
	{
		if(*(pLineArray + i) == BLACKtem) *(pLineArray + i) = BLACK;
		else if(*(pLineArray + i) == WHITEtem) *(pLineArray + i) = WHITE;
		else if(*(pLineArray + i) != WHITE && *(pLineArray + i) != BLACK)  *(pLineArray + i) = 0;
	}
}

