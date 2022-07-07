.386
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  msvcrt.lib
  putchar     PROTO C :byte  ;	显示给定 ASCII 对应的字符
.STACK 200
.CODE
 START: 
   CALL DISPLAY
   MSG1 DB 'Very Good',0DH,0AH,0
   CALL DISPLAY
   MSG2 DB '12345',0DH,0AH,0
   INVOKE ExitProcess, 0
DISPLAY:
    DB 5bH,80H,3bH,00,74H,0eH,8aH,03H,50H,0e8H,1fH,00
    DB 00,00,83H,0c4H,04H,43H,0ebH,0edH,43H,53H,0c3H
END START 