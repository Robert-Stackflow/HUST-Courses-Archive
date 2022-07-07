.686P
.model flat, c
ExitProcess proto stdcall :dword
printf proto c :ptr sbyte, :vararg
includelib kernel32.lib
includelib libcmt.lib
includelib legacy_stdio_definitions.lib
.DATA
STR1 db "abc",0
STR2 db "abd",0
outFmt DB "%d", 0
.STACK 1024
.CODE
main proc
 PUSH OFFSET STR2
 PUSH OFFSET STR1
 call STRCMP
 invoke printf,offset outFmt,eax
 invoke ExitProcess, 0
main endp
STRCMP PROC C
 PUSH EBP
 mov ebp,esp
 PUSH ESI
 PUSH EDI
 MOV ESI,[esp+4] ; （ESI） 为后入栈的串的首地址
 MOV EDI,[esp+8]
 LP: MOV AL, [ESI]
 CMP AL, [EDI]
 ja BIGGER
 jb SMALLER
 CMP AL, 0
 JZ STR_EQU
 INC ESI
 inc edi
 JMP LP
BIGGER:
 mov eax,1
 JMP EXIT
SMALLER:
 MOV EAX, -1
 JMP EXIT
STR_EQU:
 MOV EAX, 0
EXIT:
 POP EDI
 POP ESI
 mov esp,ebp
 POP EBP
 ret
STRCMP ENDP
end