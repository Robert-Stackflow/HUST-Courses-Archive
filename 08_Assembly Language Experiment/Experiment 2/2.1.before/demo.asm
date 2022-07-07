.686P     
.model flat, stdcall
 ExitProcess PROTO STDCALL :DWORD
 includelib  kernel32.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 printf proto c :vararg

  tuple struct
	SDA		dd	0
	SDB		dd	0
	SDC		dd	0
	SF      dd  0
  tuple ends

.DATA
  timeBuf		db	"Time: %u",0ah,0dh,0
  numBuf        db  "Number of Test: %u",0ah,0dh,0
  LOWF			tuple 6 DUP(<0, 0, 0>)
  MIDF			tuple 6 DUP(<0, 0, 0>)
  HIGHF			tuple 6 DUP(<0, 0, 0>)
  stream		tuple <250000,-1024,1300,0>
				tuple <1,2,3,0>
				tuple <2500,2,3,0>
				tuple <25000, 30000, 7000, 0> 
				tuple <-10110, -9333, 5678, 0> 
				tuple <-12400, 29234, 9543, 0>				
  indexLOW		dd  0
  indexMID		dd  0
  indexHIGH		dd  0
  numofTest		dd  0
.STACK 200
.CODE
main proc c
	RDTSC
	push eax
	push edx
_BEGIN:
	mov indexLOW,0
	mov indexMID,0
	mov indexHIGH,0
	mov ecx,0
_READ:
	mov  eax,stream[ecx].SDA
	mov  ebx,5
	imul ebx
	add  eax, stream[ecx].SDB
	sub  eax, stream[ecx].SDC
	add  eax, 100
	cdq
	mov ebx,128
	idiv ebx
	mov  stream[ecx].SF, eax
	cmp  eax, 100
	je   _MID
	cmp  eax, 100
	jl   _LOW
	cmp  eax, 100
	jg   _HIGH
_MID:
    mov edi,indexMID
	mov eax, stream[ecx].SDA
	mov MIDF[edi].SDA,eax
	mov eax, stream[ecx].SDB
	mov MIDF[edi].SDB,eax
	mov eax, stream[ecx].SDC
	mov MIDF[edi].SDC,eax
	mov eax, stream[ecx].SF
	mov MIDF[edi].SF,eax
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
	mov eax, stream[ecx].SF
	mov LOWF[edi].SF,eax
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
	mov eax, stream[ecx].SF
	mov HIGHF[edi].SF,eax
	add indexHIGH,12
	jmp _CIRC
_CIRC:
	add ecx,12
	cmp ecx,72
	jnz _READ
	inc numofTest
	cmp numofTest,100000000
	jnz _BEGIN
_EXIT:
	RDTSC
	pop ebx
	pop ecx
	sub eax,ecx
	sbb edx,ebx
	invoke printf, offset timeBuf,eax
	invoke printf, offset numBuf,numofTest
	invoke ExitProcess, 0
main endp
END