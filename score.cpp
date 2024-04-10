# include <iostream>
# include "gobang.h"


void ChangeScoreBoard(int x, int y, int (*pBoard)[15])	// 更新分数板 
{
	int i;
	
	//落子位置值为-1 
	ScoreBoard_b[x][y] = -1;
	ScoreBoard_w[x][y] = -1;
	
	//对2种棋子4个方向临近4格之内的32个位置共64个值重新评分 
	//竖 
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || i == 4) continue;
		if(ScoreBoard_w[x-4+i][y] != -1)
		{
			ScorePosi(x-4+i, y, pBoard, BLACK);
			ScorePosi(x-4+i, y, pBoard, WHITE);
		}
	}
	
	//左下-右上
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || y+4-i < 0 || y+4-i > 14 || i == 4) continue;
		if(ScoreBoard_w[x-4+i][y+4-i] != -1)
		{
			ScorePosi(x-4+i, y+4-i, pBoard, BLACK);
			ScorePosi(x-4+i, y+4-i, pBoard, WHITE);
		}
	}
	
	//横
	for(i=0; i<9; i++)
	{
		if(y+4-i < 0 || y+4-i > 14 || i == 4) continue;
		if(ScoreBoard_w[x][y+4-i] != -1)
		{	
			ScorePosi(x, y+4-i, pBoard, BLACK);
			ScorePosi(x, y+4-i, pBoard, WHITE);
		}
	}
	
	//左上-右下 
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


void ScorePosi(int x, int y, int (*pBoard)[15], int side) // 对特定位置打分 
{	
	int i, j, flag_b, flag_w;
	
	// 判定位置是否是合法的落子位置 
	if(ScoreBoard_b[x][y] == -1 || ScoreBoard_w[x][y] == -1) return;
	
	//获取4个方向的临近的棋盘数据，利用LineState判定棋型，结果记录在LineStateRecord中 
	//横
	for(i=0; i<=9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14) LineArray[i] = op(side);	// 超出棋盘边界的认为是对方棋子 
		else if(i == 4) LineArray[i] = side;					// 中心位置预设为自己的棋子（实际上没有棋子） 
		else
		{
			LineArray[i] = pBoard[15*(x-4+i)][y] ;
		}
	}
	LineStateRecord[LineState(LineArray)] += 1;
	
	//左下-右上
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
	
	//竖
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
	
	//左上-右下 
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
	
	
	//根据得到的棋型数据进行估值
	int score = 0;
	if(side == BLACK || side == BLACKtem)
	{
		//禁手位置评分为-2 
		if(LineStateRecord[CL] && !LineStateRecord[L5]) score = -2; 
		else if(LineStateRecord[L3] >= 2 && !LineStateRecord[L5]) score = -2;
		else if((LineStateRecord[L4] + LineStateRecord[S4] >= 2) && !LineStateRecord[L5]) score = -2;
		// 越强大的棋型分值越高，自己的同等棋型比对方的同等棋型分值高，非必须防守的对方棋型分值较低 
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
			// 相邻的棋子会加减分，这是因为我们更倾向于选择连子而非跳子	
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
	
	//把记录棋型的数组清空
	for(i = 0; i <= 8; i++)
	{
		LineStateRecord[i] = 0;
	}
}


int LineState(int *pLineArray) 						//判定某一方向上的棋型 
{	
	ChangeLine(pLineArray); //把棋型处理成需要的形式 
	
	int u = 8, l = 0, i, j, flag, side = *(pLineArray + 4);
	
	//u和l是判定区间的上下界 （对方棋子和连续空位是边界，边界外不需要判断） 
	//对方棋子边界 
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
	//连续空位边界 
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

	//对于边界内的棋型进行判定，输出最强力的棋型 
	// 判定顺序由强到弱 
	int cnt, cnt_max, sum;
	int flag_l, flag_u;
	
	flag_l = l; flag_u = u;
	cnt = 0; cnt_max = 0;

	for(i = l; i <= u; i++)		//获取最大的连续棋子数 cnt_max 
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
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == 0) return L4;	// 根据边界判定棋型是活还是眠 
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
	if(u - l + 1 >= 5)	//判定跳棋型 
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


void ChangeLine(int *pLineArray)	//把棋型处理成需要的形式 
{
	int i;
	//修改tem，无棋子处为0 
	for(i = 0; i < 9; i++)
	{
		if(*(pLineArray + i) == BLACKtem) *(pLineArray + i) = BLACK;
		else if(*(pLineArray + i) == WHITEtem) *(pLineArray + i) = WHITE;
		else if(*(pLineArray + i) != WHITE && *(pLineArray + i) != BLACK)  *(pLineArray + i) = 0;
	}
}

