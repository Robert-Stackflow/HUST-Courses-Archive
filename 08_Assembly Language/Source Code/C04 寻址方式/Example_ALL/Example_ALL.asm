; 功能，求以变量x为起始地址的4个双字的和，并显示结果
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
   ;方法1： 用寄存器间接寻址方式，访问数组x中的各个单元的内容
   ;  用 eax 来存放所求的 和
   ;  用 ebx 来指向要访问的数据，即ebx中的值为操作数的地址
   ;  用 ecx 来控制循环次数，每循环一次，ecx减1。当减到值为0时，循环结束
   ;  类似C语句 eax=0; ebx=&(x[0]); ecx=4; 
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

   ;方法2： 用变址寻址方式，访问数组x中的各个单元的内容
   ;  用 eax 来存放所求的 和
   ;  用 ebx 来表示待访问的数组元素的下标
   ;  类似C语句 eax=0;  for (ebx=0;ebx<4;ebx++) eax+=x[ebx]
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

   ;方法3： 用基址加变址寻址方式，访问数组x中的各个单元的内容
   ;  用 eax 来存放所求的 和
   ;  用 ebx 来表示待访问的数组的起始地址；
   ;  用 esi 来表示待访问的数组元素的下标
   ;  类似C语句 eax=0;  for (esi=0;esi<4;esi++) eax+=[ebx][esi]
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

   ;方法4： 用直接寻址方式，访问数组x中的各个单元的内容
   ;  用 eax 来存放所求的 和
   mov  eax, x
   add  eax, x[4]
   add  eax, x+8
   add  eax, [x+12]
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
main endp
end