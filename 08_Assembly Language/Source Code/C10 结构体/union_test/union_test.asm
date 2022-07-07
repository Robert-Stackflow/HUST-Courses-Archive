.686P
.model flat, c
  ExitProcess proto stdcall :dword
  scanf       proto :ptr sbyte, :VARARG
  includelib  msvcrt.lib
myunion   union 
         num    dword  0
         chars  byte 4 dup(0)
myunion   ends

.data
lpfmt db '%s',0
u1  myunion <34353637H>
.stack 200
.code
 start:  
    mov  eax, U1.num
	mov  AL, U1.chars[2]
	lea  ebx, U1
	mov  AL, [ebx].myunion.chars[2]

    invoke  ExitProcess, 0
end start
