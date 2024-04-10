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

# define CL 0 	// 长连 
# define L5 1 	// 连5 
# define L4 2 	// 活4
# define S4 3 	// 冲4
# define L3 4 	// 活3
# define S3 5 	// 眠3
# define L2 6 	// 活2 
# define S2 7 	// 眠2 
# define NTH 8 	//附近有棋子 

# define op(A) ((A == BLACK) ? WHITE : BLACK)  //转换 
# define max(A, B) (((A) > (B)) ? (A) : (B))
# define min(A, B) (((A) < (B)) ? (A) : (B))


extern int Board[SIZE][SIZE];       	// 棋盘 
extern int ScoreBoard_b[SIZE][SIZE];	// 黑子计分板 
extern int ScoreBoard_w[SIZE][SIZE];	// 白子计分板 

extern int mode; 						//0为人人对战，1为人机对战 
extern int side_p, side_ai;			// 记录选边情况 
extern int Posi[2];					// 记录落子位置 
extern int LineArray[9];				// 记录单一方向的落子情况 
extern int LineStateRecord[9];			// 记录某一位置可能形成的棋型，索引对应着棋型（见宏） 

//display
void DisplayBoard();

//judge
int judge(int x, int y); 		// 裁判 ，判断胜负和禁手 
void ChooseMode(); 				// 人人或人机 
void ChooseSide();  			// 选边 
int RestrictedMove(int x, int y); // 禁手判定 

//move
void MoveP(int *pBoard, int piece);	// 人落子 
void MoveAi(int piece); 			//ai落子 

//score
void ChangeScoreBoard(int x, int y, int (*pBoard)[15]); 		// 更新分数板 
void ScorePosi(int x, int y, int (*pBoard)[15], int side); 	//对特定位置打分 
int LineState(int *pLineArray); 						//输出一行中最强的棋型 
void ChangeLine(int *pLineArray); 						//将LineArray处理成需要的形式 


//board_array
void InitBoardArray();  			//初始化空棋盘
void ChangeTemPieces(int piece); 	//将tem棋子转化为正常棋子 
void PrintBoardArray(int *pBoard); 	//用于测试 



#endif
