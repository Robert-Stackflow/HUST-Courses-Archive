.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
;  includelib      msvcrt.lib
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
.data
  lpFmt	db	"x=%d y=%d r=%d",0ah, 0dh, 0
  x  sdword  -5
  y  sdword  -6
  r  sdword  0
.stack 200
.code
 ;start: 
 main  proc  c
   cmp  x, 0
   js   X_Negative
         ; �˴�������  X>=0 �����
   cmp  y, 0 
   js   X_Positive_Y_Negative
   mov  r, 1
   jmp  exit
X_Positive_Y_Negative:
   mov  r, 0
   jmp  exit
         ; ���ˣ�x>=0 ������������
		 ; ������ x<0�����
X_Negative:
   cmp y, 0
   js  X_Negative_Y_Negative
   mov r, 0
   jmp exit
X_Negative_Y_Negative:
   mov  r,-1
exit:
   invoke printf,offset lpFmt,x,y,r
   invoke ExitProcess, 0
main  endp
;end start 
end