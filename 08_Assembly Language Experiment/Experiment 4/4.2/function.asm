.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 printf PROTO C :VARARG
 VirtualProtect proto stdcall:dword,:dword,:dword,:dword

  include struct.asm

extern LOWF:tuple,MIDF:tuple,HIGHF:tuple,stream:tuple,indexLOW:dword,indexMID:dword,indexHIGH:dword,numofTest:dword,printTupleBuf:byte,printBuf:byte,calculateTip:byte,displayTip:byte;

.DATA
	abstractCode  db 06BH,004H,00EH,005H,003H,044H,00EH,004H,02BH,044H,00EH,008H,083H,0C0H,064H,0C1H,0F8H,007H,0C3H
	abstractCodeLen=$-abstractCode
	copyFinished  dd 0
	oldprotect DD ?
.STACK 200
.CODE
calculate proc
    cmp copyFinished,0
	jne abstractCodeDes
	mov eax,abstractCodeLen
	mov ebx,40h
	lea ecx,abstractCodeDes
	invoke VirtualProtect,ecx,eax,ebx,offset oldprotect
 	mov esi,offset abstractcode
	mov edi,offset abstractCodeDes
	mov ecx,abstractCodeLen
	mov copyFinished,1
copycode:
	mov al,[esi]
	mov	[edi],al
	inc esi
	inc edi
	loop copyCode
	mov esi, offset stream
abstractCodeDes:
	db abstractCodeLen dup(0)
	;imul eax, [ESI+ecx].tuple.SDA,5
	;add  eax, [ESI+ecx].tuple.SDB
	;sub  eax, [ESI+ecx].tuple.SDC
	;add  eax, 100
	;sar  eax, 7
	;ret
calculate endp

copy proc
	push eax
	push ebx
	push ecx
	push esi
	push edi
	mov numofTest,0
	invoke printf,offset printBuf,offset calculateTip
_BEGIN:
	mov indexLOW,0
	mov indexMID,0
	mov indexHIGH,0
	xor ecx,ecx
_READ:
	invoke calculate
	cmp  eax,100
	je   _MID
	jl   _LOW
	jg   _HIGH
_MID:
    mov edi,indexMID
	mov eax, stream[ecx].SDA
	mov MIDF[edi].SDA,eax
	mov eax, stream[ecx].SDB
	mov MIDF[edi].SDB,eax
	mov eax, stream[ecx].SDC
	mov MIDF[edi].SDC,eax
	add indexMID,12
	jmp _CIRC
_LOW:
	mov edi,indexLOW
	mov eax, stream[ecx].SDA
	mov LOWF[edi].SDA,eax
	mov eax, stream[ecx].SDB
	mov LOWF[edi].SDB,eax
	mov eax, stream[ecx].SDC
	mov LOWF[edi].SDC,eax
	add indexLOW,12
	jmp _CIRC
_HIGH:
	mov edi,indexHIGH
	mov eax, stream[ecx].SDA
	mov HIGHF[edi].SDA,eax
	mov eax, stream[ecx].SDB
	mov HIGHF[edi].SDB,eax
	mov eax, stream[ecx].SDC
	mov HIGHF[edi].SDC,eax
	add indexHIGH,12
	jmp _CIRC
_CIRC:
	add ecx,12
	cmp ecx,72
	jnz _READ
	inc numofTest
	cmp numofTest,100
	jnz _BEGIN
_RETURN:
	pop edi
	pop esi
	pop ecx
	pop ebx
	pop eax
	ret
copy endp

display proc
	push ebx
	invoke printf,offset printBuf,offset displayTip
	xor ebx,ebx
	.while(ebx < indexMID)
		invoke printf, offset printTupleBuf, MIDF[ebx].SDA, MIDF[ebx].SDB,MIDF[ebx].SDC
		add ebx,12
	.endw
	pop ebx
	ret
 display endp
 END