; 功能，求以变量x为起始地址的4个双字的和，并显示结果
.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  printf      PROTO C :ptr sbyte, :VARARG
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
 
.DATA
  lpFmt	db	"%d",0ah, 0dh, 0
  TAB   DB '0123456789ABCDEF'
  X     dd  10, 20, 30, 40, 50
        dd  60, 70, 80, 90, 100
		dd  110,120,130,140,150
  i     dd  1
  j     dd  2 
  R     SBYTE '12345'
  R2    SWORD 2
  R3    SDWORD 3
  R4    DD  X-4
  F1    REAL4 1.0
  F2    REAL8 2.0
.STACK 200
.CODE
main proc c
 ;   MOV  BX,OFFSET TAB
    MOV  EAX,[EBX+ECX*4]
	MOV  EAX,[ECX+EBX*4]
	MOV  EAX,[EBX+ECX*4]+5

	MOV  EBX,[ECX]
	MOV  BX, [ECX]
	MOV  BL, [ECX]
	MOV  [ECX],EBX
;	MOV AX,[BX]
	MOV AX,[EBX]
		MOV AX,cs:[EBX]
;   MOV EBX, OFFSET TAB
;   MOV EAX, CS:[EBX]
;   MOV EAX,[EBX]
 ;  MOV AL, 10
 ;  MOVZX EAX,AL
 ;  MOV AL, TAB[EAX]
   
 ;  IMUL EBX, i, 4*5
 ;  MOV  ESI, j
 ;  MOV  EAX, X[EBX][ESI*4]

   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
main endp
END
