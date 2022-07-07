.686     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib  ; ExitProcess 在 kernel32.lib中实现
 includelib  libcmt.lib

.DATA
 buf    DD  1,2,3,4,4,5,6,6,7,8,9,9,5,6,7,8,2,3,4,6,23,5,6,7,8,6,7
 LOWF   DD 27 DUP(0)
 MIDF   DD 27 DUP(0)
 HIGHF  DD 27 DUP(0)
 LEN    DD 3 DUP(0)    ;low mid high
 SAMID  DB  9 DUP(0)   ;每组数据的流水号（可以从1开始编号）
 SDA    DD  0          ;状态信息a
 SDB    DD  0          ;状态信息b
 SDC    DD  0          ;状态信息c
 SF     DD  0          ;处理结果f

.STACK 200
.CODE
main proc c
	mov ecx,0
P:
	mov ebx,buf[ecx*4]
	mov SDA,ebx
	inc ecx
	mov ebx,buf[ecx*4]
	mov SDB,ebx
	inc ecx
	mov ebx,buf[ecx*4]
	mov SDC,ebx
	inc ecx
	mov eax,SDA
	imul eax,5
	add eax,SDB
	sub eax,SDC
	add eax,100
	cdq
	mov ebx,128
	idiv ebx
	mov SF,eax
	cmp SF,100
	jg _HIGH
	je _MID
	jl _LOW
Q:
	cmp ecx,27
	jz exit
	jmp P
_HIGH:
	mov eax,LEN[2]
	mov ebx,SDA
	mov HIGHF[eax*4],ebx
	inc eax
	mov ebx,SDB
	mov HIGHF[eax*4],ebx
	inc eax
	mov ebx,SDC
	mov HIGHF[eax*4],ebx
	inc eax
	mov LEN[2],eax
	jmp Q
_MID:
	mov eax,LEN[1]
	mov ebx,SDA
	mov MIDF[eax*4],ebx
	inc eax
	mov ebx,SDB
	mov MIDF[eax*4],ebx
	inc eax
	mov ebx,SDC
	mov MIDF[eax*4],ebx
	inc eax
	mov LEN[1],eax
	jmp Q
_LOW:
	mov eax,LEN[0]
	mov ebx,SDA
	mov LOWF[eax*4],ebx
	inc eax
	mov ebx,SDB
	mov LOWF[eax*4],ebx
	inc eax
	mov ebx,SDC
	mov LOWF[eax*4],ebx
	inc eax
	mov LEN[0],eax
	jmp Q
exit:
	invoke ExitProcess,0
main endp
END