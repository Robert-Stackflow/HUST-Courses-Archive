.686P
.model flat, stdcall
 ExitProcess proto stdcall :dword
 includelib kernel32.lib
 printf proto c :ptr sbyte, :vararg
 scanf proto c:ptr sbyte, :vararg ; * proto ����ȷ�÷�
includelib libcmt.lib
 includelib legacy_stdio_definitions.lib
.data
buf db 10 dup(0) 
 outputFmt db "%d",0ah, 0dh,0 ;* ������ʱ��Ҫע���ϸ��
 inputFmt db "%s", 0
.stack 200
.code
main proc c
 invoke scanf, offset inputFmt,offset buf ; * c ���Եĵ�����ʽ�� scanf(��%d��,&x)
 MOV EAX, 0
 MOV BX, 10
 MOV ESI, 0 ; * (ESI) �Ƿ���Ԫ�ص��±�
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
 invoke printf,offset outputFmt, eax ; *������Ҫʹ�õ�ַ
 invoke ExitProcess, 0
 main endp
end