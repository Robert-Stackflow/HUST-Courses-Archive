#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

int Menu(){
	printf("=========================\n");
	printf("**��ӭ������������Ϸ**\n");
	printf("========================\n");
	printf("1.��ʾ��ʼ��Ϸ \n");
	printf("0.��ʾ������Ϸ\n");
	printf("O��ʾ��������\n");
	printf("x��ʾ��ҵ�����\n");
	int choice = 0;
	printf("���������ѡ��: \n");
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
		printf("  %d ", i); //��ӡ���� x ��������ʾ
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
	printf("�ֵ��������!\n");
	while (1){
		int row = 0;
		int col = 0;
		printf("������Ҫ���ӵ�λ��(row,col): \n");
		scanf("%d %d", &row, &col);
		if (row < 0 || row >= Max_Row || col<0 || col >= Max_col){
			printf("������������,����������\n");
			continue;
		}
		if (chessBoard[row][col] != ' '){
			printf("��λ��������,����������\n");
			continue;
		}
		chessBoard[row][col] = 'X';
		break;
	}
}
//����4.�鿴��Ϸ�Ƿ���� ����6.�鿴��Ϸ�Ƿ����
///*����ֵ������ǰ��Ϸ״��;
//1.����X��ʾ��һ�ʤ
//2.����O��ʾ���Ի�ʤ
//3.����' '��ʾ��δ�ֳ�ʤ��
//4.����Q��ʾ����*/

char Check(char chessBoard[Max_Row][Max_col]){
	//1.������һ����,Ӯ�Ҳ���
	for (int i = 0; i < Max_Row; i++){
		for (int j = 0; j < Max_col - 4; j++){
			if (chessBoard[i][j] != ' ' &&chessBoard[i][j] == chessBoard[i][j + 1] && chessBoard[i][j] ==
				chessBoard[i][j + 2] && chessBoard[i][j] == chessBoard[i][j + 3] && chessBoard[i][j] ==
				chessBoard[i][j + 4]){
				return chessBoard[i][j];
			}
		}
	}

//2.������һ����,Ӯ�Ҳ���
	for (int j = 0; j < Max_col; j++){
		for (int i = 0; i < Max_col - 4; i++){
			if (chessBoard[i][j] != ' '&&chessBoard[i][j] == chessBoard[i + 1][j] && chessBoard[i][j] ==
				chessBoard[i + 2][j] && chessBoard[i][j] == chessBoard[i + 3][j] && chessBoard[i][j] ==
				chessBoard[i + 4][j]){
				return chessBoard[i][j];
			}
		}
	}
//3.�Խ�������һ����,Ӯ�Ҳ���

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

	//4.�ж��Ƿ��Ǻ���,������˾��Ǻ���
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
		printf("�ֵ���������!\n");
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
		//1.��ʼ������
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
		printf("��ϲ��,��Ӯ��!\n");
	}
	else if (winter == 'O'){
		printf("�����,�����Զ��Ų���\n");
	}
	else{
		printf("�����,�͵������忪\n");
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
			printf("������������\n");
			break;
		}
	}
	system("pause");
	return 0;
}

