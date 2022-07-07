.686P
.model flat, stdcall
 ExitProcess proto stdcall :dword
 includelib kernel32.lib
 printf proto c :ptr sbyte, :vararg
 scanf proto c:ptr sbyte, :vararg ; * proto 的正确用法
includelib libcmt.lib
 includelib legacy_stdio_definitions.lib
.data
buf db 10 dup(0) 
 outputFmt db "%d",0ah, 0dh,0 ;* 串定义时需要注意的细节
 inputFmt db "%s", 0
.stack 200
.code
main proc c
 invoke scanf, offset inputFmt,offset buf ; * c 语言的调用形式是 scanf(“%d”,&x)
 MOV EAX, 0
 MOV BX, 10
 MOV ESI, 0 ; * (ESI) 是访问元素的下标
LP: 
 MOVZX CX,byte ptr BUF[ESI] ; * 
 CMP CL, 0
 JZ EXIT
 MUL BX ; *
 SUB CL, '0'
 ADD AX,CX; *
 INC ESI ; *
 JMP LP ; *
EXIT:
 invoke printf,offset outputFmt, eax ; *参数需要使用地址
 invoke ExitProcess, 0
 main endp
end