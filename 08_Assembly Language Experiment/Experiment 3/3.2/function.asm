.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib
 includelib  legacy_stdio_definitions.lib
 printf PROTO C :VARARG
 scanf	PROTO C :VARARG
 getchar PROTO  C:VARARG
 public indexMID,LOWF,MIDF,HIGHF,stream
 tuple struct
	SDA		dd	0
	SDB		dd	0
	SDC		dd	0
 tuple ends

.DATA
  LOWF     dd 18 DUP(0)
  MIDF     dd 18 DUP(0)
  HIGHF    dd 18 DUP(0)
  indexLOW dd 0
  indexMID dd 0
  indexHIGH dd 0
  stream		tuple <250000,-1024,1300>
				tuple <1,2,3>
				tuple <2560,0,100>
				tuple <25000, 30000, 7000>
				tuple <-10110, -9333, 5678>
				tuple <-12400, 29234, 9543>
.STACK 200
.CODE

calculate proc SDA:dword, SDB:dword,SDC:dword
	imul eax, SDA,5
	add  eax, SDB
	sub  eax, SDC
	add  eax, 100
	sar  eax, 7
	ret
calculate endp

copy proc
	push eax
	push ebx
	push ecx
	push esi
	push edi
_BEGIN:
	mov indexLOW,0
	mov indexMID,0
	mov indexHIGH,0
	xor ecx,ecx
_READ:
	invoke calculate,stream[ecx].SDA,stream[ecx].SDB,stream[ecx].SDC
	cmp  eax,100
	je   _MID
	jl   _LOW
	jg   _HIGH
_MID:
    mov edi,indexMID
	mov eax, stream[ecx].SDA
	mov MIDF[edi],eax
	mov eax, stream[ecx].SDB
	mov MIDF[edi+4],eax
	mov eax, stream[ecx].SDC
	mov MIDF[edi+8],eax
	add indexMID,12
	jmp _CIRC
_LOW:
	mov edi,indexLOW
	mov eax, stream[ecx].SDA
	mov LOWF[edi],eax
	mov eax, stream[ecx].SDB
	mov LOWF[edi+4],eax
	mov eax, stream[ecx].SDC
	mov LOWF[edi+8],eax
	add indexLOW,12
	jmp _CIRC
_HIGH:
	mov edi,indexHIGH
	mov eax, stream[ecx].SDA
	mov HIGHF[edi],eax
	mov eax, stream[ecx].SDB
	mov HIGHF[edi+4],eax
	mov eax, stream[ecx].SDC
	mov HIGHF[edi+8],eax
	add indexHIGH,12
	jmp _CIRC
_CIRC:
	add ecx,12
	cmp ecx,72
	jnz _READ
_RETURN:
	pop edi
	pop esi
	pop ecx
	pop ebx
	pop eax
	ret
copy endp
END