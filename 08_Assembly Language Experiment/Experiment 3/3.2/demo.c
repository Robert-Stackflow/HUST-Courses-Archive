#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4013)
#pragma warning(disable : 4715)
#pragma warning(disable : 6001)
#pragma warning(disable : 6031)
#pragma warning(disable : 6054)
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
struct tuple {
	int SDA;
	int SDB;
	int SDC;
};
extern struct tuple stream[];
extern int indexMID;
extern int LOWF[];
extern int MIDF[];
extern int HIGHF[];
bool login();
void order();
extern void __stdcall copy();
void display(int* MIDF);
char* defaultUsername = "xuruida";
char* defaultPassword = "123456";
int main(void)
{
	if (!login())
		return 0;
	printf("Logged in!\n");
	order();
}

bool login()
{
	bool usernameFlag = false, passwordFlag = false;
	int inputPasswordTime = 0;
	char inputUsername[20], inputPassword[20];
	while (!usernameFlag) {
		printf(">>Input your username:\n");
		gets(inputUsername);
		if (strcmp(inputUsername, defaultUsername) == 0)
			usernameFlag = true;
		else
			usernameFlag = false, printf("User not found!\n");
	}
	while (inputPasswordTime < 3)
	{
		printf(">>Input your password:\n");
		gets(inputPassword);
		if (strcmp(inputPassword, defaultPassword) == 0)
			return true;
		else
			printf("Incorrect password!\n"), inputPasswordTime++;
	}
}

void display(int* MIDF)
{
	for (int i = 0; i < indexMID / 4; i += 3)
		printf("%d,%d,%d\n", MIDF[i], MIDF[i + 1], MIDF[i + 2]);
}

void order()
{
	while (1)
	{
		copy();
		display(&MIDF[0]);
		int flag = 1;
		while (flag)
		{
			printf(">>Input your option:(R|Q|M)\n");
			int a, b, c;
			char option[20];
			scanf("%s", option);
			switch (option[0])
			{
			case 'Q':
				return;
			case 'R':
				flag = 0;
				break;
			case 'M':
				printf(">>Input your new tuple(a b c):\n");
				scanf("%d%d%d", &a, &b, &c);
				stream[0].SDA = a;
				stream[0].SDB = b;
				stream[0].SDC = c;
				break;
			default:
				printf("Invalid Input!\n");
				break;
			}
		}
	}
}