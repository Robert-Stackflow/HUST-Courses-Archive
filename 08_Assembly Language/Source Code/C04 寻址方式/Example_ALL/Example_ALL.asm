; ���ܣ����Ա���xΪ��ʼ��ַ��4��˫�ֵĺͣ�����ʾ���
.686P
.XMM
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
  printf      PROTO C :ptr sbyte, :VARARG
 
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  x     dd  10, 20, 30, 40
.STACK 200

.CODE
main proc c 
   ;����1�� �üĴ������Ѱַ��ʽ����������x�еĸ�����Ԫ������
   ;  �� eax ���������� ��
   ;  �� ebx ��ָ��Ҫ���ʵ����ݣ���ebx�е�ֵΪ�������ĵ�ַ
   ;  �� ecx ������ѭ��������ÿѭ��һ�Σ�ecx��1��������ֵΪ0ʱ��ѭ������
   ;  ����C��� eax=0; ebx=&(x[0]); ecx=4; 
   ;         do {eax+=*ebx; ebx+=1; ecx-=1}while(ecx!=0)
   mov  eax, 0
   mov  ebx, offset x
   mov  ecx, 4
lp1: 
   add  eax, [ebx]
   add  ebx, 4
   dec  ecx
   jnz  lp1
   invoke printf,offset lpFmt,eax

   ;����2�� �ñ�ַѰַ��ʽ����������x�еĸ�����Ԫ������
   ;  �� eax ���������� ��
   ;  �� ebx ����ʾ�����ʵ�����Ԫ�ص��±�
   ;  ����C��� eax=0;  for (ebx=0;ebx<4;ebx++) eax+=x[ebx]
   mov  eax, 0
   mov  ebx, 0
lp2: 
   cmp  ebx, 4
   jge  exit_2
   add  eax, x[ebx*4]
   inc  ebx
   jmp  lp2
exit_2:
   invoke printf,offset lpFmt,eax

   ;����3�� �û�ַ�ӱ�ַѰַ��ʽ����������x�еĸ�����Ԫ������
   ;  �� eax ���������� ��
   ;  �� ebx ����ʾ�����ʵ��������ʼ��ַ��
   ;  �� esi ����ʾ�����ʵ�����Ԫ�ص��±�
   ;  ����C��� eax=0;  for (esi=0;esi<4;esi++) eax+=[ebx][esi]
   mov  eax, 0
   mov  ebx, offset x
   mov  esi, 0
lp3: 
   cmp  esi, 4
   jge  exit_3
   add  eax, [ebx][esi*4]
   inc  esi
   jmp  lp3
exit_3:
   invoke printf,offset lpFmt,eax

   ;����4�� ��ֱ��Ѱַ��ʽ����������x�еĸ�����Ԫ������
   ;  �� eax ���������� ��
   mov  eax, x
   add  eax, x[4]
   add  eax, x+8
   add  eax, [x+12]
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
main endp
end