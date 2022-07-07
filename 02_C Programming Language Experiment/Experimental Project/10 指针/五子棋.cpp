#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

int Menu(){
	printf("=========================\n");
	printf("**欢迎来到五子棋游戏**\n");
	printf("========================\n");
	printf("1.表示开始游戏 \n");
	printf("0.表示结束游戏\n");
	printf("O表示电脑落子\n");
	printf("x表示玩家的落子\n");
	int choice = 0;
	printf("请输入你的选择: \n");
	scanf("%d", &choice);
	return choice;
}

#define Max_Row 10
#define Max_col 10
void Init(char chessBoard[Max_Row][Max_col]){
	srand((unsigned int)time(0));
	memset(chessBoard, ' ', Max_Row*Max_col);
}

void Print(char chessBoard[Max_Row][Max_col]){

	for (int i = 0; i < Max_Row; i++)
	{
		printf("  %d ", i); //打印棋盘 x 轴坐标提示
	}
	printf("\n");

	for (int row = 0; row < Max_Row; row++){
		printf("+---+---+---+---+---+---+---+---+---+---+\n");
		printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", chessBoard[row][0], chessBoard[row][1], chessBoard[row][2], 
			chessBoard[row][3], chessBoard[row][4], chessBoard[row][5], chessBoard[row][6], chessBoard[row][7],
			chessBoard[row][8], chessBoard[row][9]);

	}
	printf("+---+---+---+---+---+---+---+---+---+---+\n");
}


void PlayerMove(char chessBoard[Max_Row][Max_col]) {
	printf("轮到玩家落子!\n");
	while (1){
		int row = 0;
		int col = 0;
		printf("请输入要落子的位置(row,col): \n");
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= Max_Row || col<0 || col >= Max_col){
			printf("您的输入有误,请重新输入\n");
			continue;
		}
		if (chessBoard[row][col] != ' '){
			printf("该位置有子了,请重新输入\n");
			continue;
		}
		chessBoard[row][col] = 'X';
		break;
	}
}
//步骤4.查看游戏是否结束 步骤6.查看游戏是否结束
///*返回值表述当前游戏状况;
//1.返回X表示玩家获胜
//2.返回O表示电脑获胜
//3.返回' '表示还未分出胜负
//4.返回Q表示和棋*/

char Check(char chessBoard[Max_Row][Max_col]){
	//1.行连成一条线,赢家产生
	for (int i = 0; i < Max_Row; i++){
		for (int j = 0; j < Max_col - 4; j++){
			if (chessBoard[i][j] != ' ' &&chessBoard[i][j] == chessBoard[i][j + 1] && chessBoard[i][j] ==
				chessBoard[i][j + 2] && chessBoard[i][j] == chessBoard[i][j + 3] && chessBoard[i][j] ==
				chessBoard[i][j + 4]){
				return chessBoard[i][j];
			}
		}
	}

//2.列连成一条线,赢家产生
	for (int j = 0; j < Max_col; j++){
		for (int i = 0; i < Max_col - 4; i++){
			if (chessBoard[i][j] != ' '&&chessBoard[i][j] == chessBoard[i + 1][j] && chessBoard[i][j] ==
				chessBoard[i + 2][j] && chessBoard[i][j] == chessBoard[i + 3][j] && chessBoard[i][j] ==
				chessBoard[i + 4][j]){
				return chessBoard[i][j];
			}
		}
	}
//3.对角线连成一条线,赢家产生

	for (int i = 0; i < Max_col - 4; i++){
		if (chessBoard[i][i] != ' '&&chessBoard[i][i] == chessBoard[i + 1][i + 1] && chessBoard[i][i] ==
			chessBoard[i + 2][i + 2] && chessBoard[i][i] == chessBoard[i + 3][i + 3] && chessBoard[i][i] == 
			chessBoard[i + 4][i + 4]){
			return chessBoard[i][i];
		}
		if (chessBoard[i][i + 4] != ' '&&chessBoard[i][i + 4] == chessBoard[i + 1][i + 3] &&
			chessBoard[i][i + 4] == chessBoard[i + 2][i + 2] && chessBoard[i][i + 4] ==
			chessBoard[i + 3][i + 1] && chessBoard[i][i + 4] == chessBoard[i + 4][i]){
			return chessBoard[i][i + 4];
		}
	}

	//4.判定是否是和棋,如果满了就是和棋
	int IsFull(chessBoard);
	
	if (IsFull(chessBoard)){
		return 'Q';
	}
	return ' ';
}

int IsFull(char chessBoard[Max_Row][Max_col]){
	for (int row = 0; row < Max_Row; row++){
		for (int col = 0; col < Max_col; col++){
			if (chessBoard[row][col] == ' '){
				return 0;
			}
		}
	}
	return 1;
}

void ComputerMove(char chessBoard[Max_Row][Max_col]){
	while (1){
		printf("轮到电脑落子!\n");
		int row = rand() % Max_Row;
		int col = rand() % Max_col;
		if (chessBoard[row][col] != ' '){
			continue;
		}
		chessBoard[row][col] = 'O';
		break;
	}
}

void Game(){
	char chessBoard[Max_Row][Max_col] = { 0 };
	char winter = ' ';
	Init(chessBoard);
	while (1){
		//1.初始化棋盘
	    Print(chessBoard);
		PlayerMove(chessBoard);
		winter = Check(chessBoard);
		if (winter != ' '){
			break;
		}
		ComputerMove(chessBoard);
		if (winter != ' '){
			break;
		}
	}
	Print(chessBoard);
	if (winter == 'X'){
		printf("恭喜你,你赢了!\n");
	}
	else if (winter == 'O'){
		printf("你真菜,连电脑都吓不过\n");
	}
	else{
		printf("你真菜,和电脑五五开\n");
	}
	
}

int main(){
	while (1){
		int choice = Menu();
		if (choice == 1){
			Game();
		}
		else if (choice == 0){
			printf("Goodble\n");
			break;
		}
		else{
			printf("您的输入有误\n");
			break;
		}
	}
	system("pause");
	return 0;
}

