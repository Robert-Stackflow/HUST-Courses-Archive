#include <stdio.h>
int main(int argc, char* argv[])
{
	int sum;
	sum = 0;
	__asm {
		mov eax, sum; eax ������ź�
			mov ebx, 1; ebx Ϊѭ��������
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
