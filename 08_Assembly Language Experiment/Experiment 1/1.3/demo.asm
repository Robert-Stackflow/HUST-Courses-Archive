.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess �� kernel32.lib��ʵ��
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 printf PROTO C :VARARG
 scanf	PROTO C :VARARG
 getchar PROTO  C:VARARG

.DATA
  printBuf	  db  "%s",0ah,0dh,0
  printNumBuf db  "%d",0ah,0dh,0
  scanBuf db  "%s",0
  tip db '���볤�Ȳ�����10���ַ���:',0
  msg1 db '��'
  msg2 db '���',0ah,0dh,0
  defaultKey   db  'abcdefg',0
  defaultLen  equ $-defaultKey
  customKey   db 0
.STACK 200
.CODE
main proc c
   invoke printf,offset printBuf,offset tip
   invoke scanf,offset scanBuf,offset customKey
   lea esi,defaultKey
   lea edi,customKey
   mov ecx,defaultLen
   cld
   repz cmpsb
   jz equal
   invoke printf,offset msg1
   jmp exit
equal:
   invoke printf,offset msg2
exit:
   invoke getchar
   invoke Exitprocess,0
main endp
END