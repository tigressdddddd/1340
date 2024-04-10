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

# define CL 0 	 
# define L5 1 	
# define L4 2 	
# define S4 3 	
# define L3 4 	
# define S3 5 	
# define L2 6 	
# define S2 7 	
# define NTH 8 	

# define op(A) ((A == BLACK) ? WHITE : BLACK)  
# define max(A, B) (((A) > (B)) ? (A) : (B))
# define min(A, B) (((A) < (B)) ? (A) : (B))


extern int Board[SIZE][SIZE];       	// chessboard
extern int ScoreBoard_b[SIZE][SIZE];	// scoreboard for black piece
extern int ScoreBoard_w[SIZE][SIZE];	// scoreboard for white piece 

extern int mode; 						//mode 0: man vs man, mode 1: man vs machine  
extern int side_p, side_ai;			// record which side you choose 
extern int Posi[2];					// record the place where you drop the chess piece
extern int LineArray[9];				// record the dropping chess of a single side  
extern int LineStateRecord[9];			// Records possible moves in a position, with indexes corresponding to moves 

//display
void DisplayBoard();

//judge
int judge(int x, int y); 		// judge winning and restricted move 
void ChooseMode(); 				// choose mode
void ChooseSide();  			// choose edge
int RestrictedMove(int x, int y); // determine if it is a restricted move

//move
void MoveP(int *pBoard, int piece);	// player move
void MoveAi(int piece); 			//ai move

//score
void ChangeScoreBoard(int x, int y, int (*pBoard)[15]); 		// refresh the scoreboard
void ScorePosi(int x, int y, int (*pBoard)[15], int side); 	//score specific position 
int LineState(int *pLineArray); 						//output the most powerful chess type 
void ChangeLine(int *pLineArray); 						//turn LineArray into the needed format


//board_array
void InitBoardArray();  			//initialize empty chessboard
void ChangeTemPieces(int piece); 	//turn tem chess piece to normal chess piece 
void PrintBoardArray(int *pBoard); 	//for test



#endif
