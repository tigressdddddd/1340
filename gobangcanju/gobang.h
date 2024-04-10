# define _CRT_SECURE_NO_WARNINGS
# include <iostream>
using namespace std;
#ifndef GOBANG_H
#define GOBANG_H
# define SIZE 15
# define BLACKtem 10
# define WHITEtem 11
# define BLACK 20
# define WHITE 21

# define CL 0 	// ���� 
# define L5 1 	// ��5 
# define L4 2 	// ��4
# define S4 3 	// ��4
# define L3 4 	// ��3
# define S3 5 	// ��3
# define L2 6 	// ��2 
# define S2 7 	// ��2 
# define NTH 8 	//���������� 

# define op(A) ((A == BLACK) ? WHITE : BLACK)  //ת�� 




extern int Board[SIZE][SIZE];       	// ���� 
extern int ScoreBoard_b[SIZE][SIZE];	// ���ӼƷְ� 
extern int ScoreBoard_w[SIZE][SIZE];	// ���ӼƷְ� 

extern int mode; 						//0Ϊ���˶�ս��1Ϊ�˻���ս 
extern int side_p, side_ai;			// ��¼ѡ����� 
extern int Posi[2];					// ��¼����λ�� 
extern int LineArray[9];				// ��¼��һ������������ 
extern int LineStateRecord[9];			// ��¼ĳһλ�ÿ����γɵ����ͣ�������Ӧ�����ͣ����꣩ 

//display
void DisplayBoard();

//judge
int judge(int x, int y); 		// ���� ���ж�ʤ���ͽ��� 
void ChooseMode(); 				// ���˻��˻� 
void ChooseSide();  			// ѡ�� 
int RestrictedMove(int x, int y); // �����ж� 

//move
void MoveP(int *pBoard, int piece);	// ������ 
void MoveAi(int piece); 			//ai���� 

//score
void ChangeScoreBoard(int x, int y, int (*pBoard)[15]); 		// ���·����� 
void ScorePosi(int x, int y, int (*pBoard)[15], int side); 	//���ض�λ�ô�� 
int LineState(int *pLineArray); 						//���һ������ǿ������ 
void ChangeLine(int *pLineArray); 						//��LineArray��������Ҫ����ʽ 


//board_array
void InitBoardArray();  			//��ʼ��������
void ChangeTemPieces(int piece); 	//��tem����ת��Ϊ�������� 
void PrintBoardArray(int *pBoard); 	//���ڲ��� 

void chooseboard();

#endif
