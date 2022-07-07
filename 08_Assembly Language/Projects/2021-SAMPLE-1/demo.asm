.686P
.model flat, c
ExitProcess proto stdcall :dword
printf proto c :ptr sbyte, :vararg
includelib kernel32.lib
includelib libcmt.lib
includelib legacy_stdio_definitions.lib

SET_ADR MACRO BY	
 	push dword ptr[BY]
	push dword ptr[BY+4]
	mov ebx,T1
	mov dword ptr[BY],ebx
	mov ebx,T2
	mov dword ptr[BY+4],ebx
endm

.DATA
lpmft db "%d",0ah,0dh,0
RES1 DD 1
RES2 DD 2
BY DB 2 DUP (6,'7')

.STACK 1024

.CODE
main proc c
 SET_ADR BY ;在 BY 指向的缓冲区建地址表
 lea eax,BY
 mov eax,[eax+0*4]
 call eax ;转移到 t1 标号处执行
 lea eax,BY
 mov eax,[eax+1*4]
 jmp eax ;转移到 t2 标号处执行
T1: 
	mov eax,ebx
	invoke printf,offset lpmft ,RES1
T2: 
	cmp edx,ecx
	invoke printf,offset lpmft ,RES2
main endp
end