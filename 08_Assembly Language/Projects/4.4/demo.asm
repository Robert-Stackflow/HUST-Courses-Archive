.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess �� kernel32.lib��ʵ��
 printf          PROTO C :VARARG
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib

.DATA
lpFmt	db	"%s",0ah, 0dh, 0
  buf1   db  '00123456789',0
  buf2   db  12 dup(0)   ; 12���ֽڵĿռ䣬��ֵ��Ϊ 0 
.STACK 200
.CODE
main proc c
   MOV  EBX,0
L1:
   MOV  al, buf1[EBX]   ;�����������12���ֽڣ�����ÿ�δ���4���ֽ���
   MOV  buf2[EBX],al
   inc EBX
   cmp ebx,12
   JNZ  L1
   invoke printf,offset lpFmt,OFFSET buf1
   invoke printf,offset lpFmt,OFFSET buf2
   invoke ExitProcess, 0
main endp
END