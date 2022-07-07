.686P
.model flat, c
ExitProcess proto stdcall :dword
printf proto c :ptr sbyte, :vararg
includelib kernel32.lib
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
.DATA
BUF DB 'I Like Assembly Language'
LEN EQU $ - BUF
COUNT DB 26 DUP('a',30H),0
outFmt DB "%s", 0
.STACK 1024
.CODE
main proc
 LEA EDI, BUF
   MOV ECX,LEN; -------------------------------------- ¢Ù
NEXT: MOV BL, [EDI] ; -------------------------------------- ¢Ú
 CMP BL, 'a'
 JB L1
 CMP BL, 'z' ; z ÊÇÐ¡Ð´×ÖÄ¸
 JA L1
 SUB BL, 'a'
 MOVZX EBX, BL
 INC COUNT[EBX*2+1]
L1: INC EDI ; --------------------------------------- ¢Û
 DEC ECX
 JNZ NEXT
 PUSH OFFSET COUNT
 PUSH OFFSET outFmt
 CALL STROUT
L2: invoke ExitProcess, 0
main endp
STROUT PROC
 MOV ESI,[ESP+4]
 MOV EBX,[ESP+8]
 MOV ECX,25
NEXT2: ADD [EBX+ECX*2],ECX
 LOOP NEXT2
 invoke printf, ESI, EBX
 RET 8
STROUT ENDP
 END