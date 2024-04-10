# include <iostream>
# include "gobang.h"


void ChangeScoreBoard(int x, int y, int (*pBoard)[15])	// ���·����� 
{
	int i;
	
	//����λ��ֵΪ-1 
	ScoreBoard_b[x][y] = -1;
	ScoreBoard_w[x][y] = -1;
	
	//��2������4�������ٽ�4��֮�ڵ�32��λ�ù�64��ֵ�������� 
	//�� 
	
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || i == 4) continue;
		
		if(ScoreBoard_w[x-4+i][y] != -1)
		{	
			ScorePosi(x-4+i, y, pBoard, BLACK);
			ScorePosi(x-4+i, y, pBoard, WHITE);
		}
	}
	cout<<'1'<<endl;
	//����-����
	for(i=0; i<9; i++)
	{
		if(x-4+i < 0 || x-4+i > 14 || y+4-i < 0 || y+4-i > 14 || i == 4) continue;
		if(ScoreBoard_w[x-4+i][y+4-i] != -1)
		{
			ScorePosi(x-4+i, y+4-i, pBoard, BLACK);
			ScorePosi(x-4+i, y+4-i, pBoard, WHITE);
		}
	}
	
	//��
	for(i=0; i<9; i++)
	{
		if(y+4-i < 0 || y+4-i > 14 || i == 4) continue;
		if(ScoreBoard_w[x][y+4-i] != -1)
		{	
			ScorePosi(x, y+4-i, pBoard, BLACK);
			ScorePosi(x, y+4-i, pBoard, WHITE);
		}
	}
	
	//����-���� 
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


void ScorePosi(int x, int y, int (*pBoard)[15], int side) // ���ض�λ�ô�� 
{	
	int i, j, flag_b, flag_w;
	
	// �ж�λ���Ƿ��ǺϷ�������λ�� 

	if(ScoreBoard_b[x][y] == -1 || ScoreBoard_w[x][y] == -1) return;
		
	//��ȡ4��������ٽ����������ݣ�����LineState�ж����ͣ������¼��LineStateRecord�� 
	//��
	for(i=0; i<=9; i++)
	{	
		if(x-4+i < 0 || x-4+i > 14) LineArray[i] = op(side);
			// �������̱߽����Ϊ�ǶԷ����� 
		else if(i == 4) LineArray[i] = side;					// ����λ��Ԥ��Ϊ�Լ������ӣ�ʵ����û�����ӣ� 
		else
		{	
			LineArray[i] = pBoard[(x-4+i)][y];
			cout<<'1'<<endl;
		}
	}
	LineStateRecord[LineState(LineArray)] += 1;
		cout<<'1'<<endl;
	//����-����
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
	
	//��
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
	
	//����-���� 
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
	
	
	//���ݵõ����������ݽ��й�ֵ
	int score = 0;
	if(side == BLACK || side == BLACKtem)
	{
		//����λ������Ϊ-2 
		if(LineStateRecord[CL] && !LineStateRecord[L5]) score = -2; 
		else if(LineStateRecord[L3] >= 2 && !LineStateRecord[L5]) score = -2;
		else if((LineStateRecord[L4] + LineStateRecord[S4] >= 2) && !LineStateRecord[L5]) score = -2;
		// Խǿ������ͷ�ֵԽ�ߣ��Լ���ͬ�����ͱȶԷ���ͬ�����ͷ�ֵ�ߣ��Ǳ�����صĶԷ����ͷ�ֵ�ϵ� 
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
			// ���ڵ����ӻ�Ӽ��֣�������Ϊ���Ǹ�������ѡ�����Ӷ�������	
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
	
	//�Ѽ�¼���͵��������
	for(i = 0; i <= 8; i++)
	{
		LineStateRecord[i] = 0;
	}
}


int LineState(int *pLineArray) 						//�ж�ĳһ�����ϵ����� 
{	
	ChangeLine(pLineArray); //�����ʹ�������Ҫ����ʽ 
	
	int u = 8, l = 0, i, j, flag, side = *(pLineArray + 4);
	
	//u��l���ж���������½� ���Է����Ӻ�������λ�Ǳ߽磬�߽��ⲻ��Ҫ�жϣ� 
	//�Է����ӱ߽� 
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
	//������λ�߽� 
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

	//���ڱ߽��ڵ����ͽ����ж��������ǿ�������� 
	// �ж�˳����ǿ���� 
	int cnt, cnt_max, sum;
	int flag_l, flag_u;
	
	flag_l = l; flag_u = u;
	cnt = 0; cnt_max = 0;

	for(i = l; i <= u; i++)		//��ȡ�������������� cnt_max 
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
		if(*(pLineArray + flag_l) + *(pLineArray + flag_u) == 0) return L4;	// ���ݱ߽��ж������ǻ���� 
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
	if(u - l + 1 >= 5)	//�ж������� 
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


void ChangeLine(int *pLineArray)	//�����ʹ�������Ҫ����ʽ 
{
	int i;
	//�޸�tem�������Ӵ�Ϊ0 
	for(i = 0; i < 9; i++)
	{
		if(*(pLineArray + i) == BLACKtem) *(pLineArray + i) = BLACK;
		else if(*(pLineArray + i) == WHITEtem) *(pLineArray + i) = WHITE;
		else if(*(pLineArray + i) != WHITE && *(pLineArray + i) != BLACK)  *(pLineArray + i) = 0;
	}
}

