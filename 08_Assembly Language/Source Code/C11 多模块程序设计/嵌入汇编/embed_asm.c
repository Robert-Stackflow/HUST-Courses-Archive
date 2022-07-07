#include <stdio.h>
int main(int argc, char* argv[])
{
	int sum;
	sum = 0;
	__asm {
		mov eax, sum; eax 用来存放和
			mov ebx, 1; ebx 为循环计算器
		L1 :
		cmp  ebx, 100
			jg   L2
			add  eax, ebx
			inc  ebx
			jmp  L1
			L2 : mov  sum, eax

	}
	printf("%d\n", sum);
	return 0;
}
