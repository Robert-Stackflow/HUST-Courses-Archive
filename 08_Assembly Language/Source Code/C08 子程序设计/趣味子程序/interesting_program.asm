.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  VirtualProtect PROTO STDCALL :DWORD, :DWORD,:DWORD,:DWORD
  includelib  kernel32.lib
;  includelib  msvcrt.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  putchar     PROTO C :byte  ;	显示给定 ASCII 对应的字符
.STACK 200
.DATA
 MACHINE_CODE DB 0E8H,20H,0,0,0
              DB 'Very Good',0DH,0AH,0
			  DB   0E8H,0FH,0,0,0
			  DB '12345',0DH,0AH,0
 LEN = $-MACHINE_CODE
 oldprotect   DD  ?
.CODE
main  proc  c
    MOV  EAX,LEN
	MOV  EBX, 40H
	LEA  ECX, CopyHere
    invoke VirtualProtect,ECX,EAX,EBX,offset oldprotect
;   CALL DISPLAY
;   DB   0E8H,20H,0,0,0
;   MSG1 DB 'Very Good',0DH,0AH,0
;   DB   0E8H,0FH,0,0,0
;   CALL DISPLAY
;   MSG2 DB '12345',0DH,0AH,0
    MOV  ECX,LEN
	MOV  EDI,OFFSET CopyHere
    MOV  ESI,OFFSET MACHINE_CODE
CopyCode:
    MOV  AL, [ESI]
	MOV  [EDI],AL
	INC  ESI
	INC  EDI
	LOOP CopyCode
CopyHere:
   DB LEN DUP(0)
   INVOKE ExitProcess, 0
main  endp
; ________________________________
; 子程序：显示一个字符串 
DISPLAY PROC
   POP  EBX
LP:
   CMP  BYTE PTR [EBX],0
   JZ   EXIT
   INVOKE  PUTCHAR, BYTE PTR [EBX] 
   INC  EBX
   JMP  LP
EXIT:
   INC  EBX
   PUSH EBX
   RET   
DISPLAY ENDP
END