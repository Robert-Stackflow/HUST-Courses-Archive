   ; MOVD   MM3, 123      ; Invalid instruction operands
   ; MOVD  MM3, [EAX]   ; Invalid instruction operands
   ; MOVD  EAX, EBX       ; invalid instruction operands

.686P
.XMM
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
.DATA
  lpFmt	db	"%s",0ah, 0dh, 0
  X     DB   70H, 0A0H, 50H,  50H, 0F0H, 0F0H, 0F0H, 0F0H
  Y     DB  0A0H,  70H, 30H, 0F0H,  01H,  20H,  81H, 0F0H
  XW    DW  9ABCH, 5678H, 0234H,  0001H
  YW    DW  0067H,  8ABCH, 6789H,  0045H
  Z     DB  8 DUP(0)
  MSG1  DB  'Hello,One',0
  MSG2  DB  'Two',0
  MSG3  DB  'Welcome,Three',0
  VTABLE  DD  MSG1, MSG2, MSG3
.STACK 200
.CODE
 START: 
 mov  al,70h
 mov  ah,0a0h
 add  al,ah
 ;  MOVQ  MM0, QWORD PTR XW
 ; MOVD  DWORD PTR Y, MM0
 movq mm0, qword ptr x
 movq mm1, qword ptr y
 psubsb  mm0,mm1
   MOVQ  MM1, QWORD PTR YW
;   PACKSSWB MM0,MM1
;   PUNPCKHBW MM0,MM1
 ;  EMMS

;   PCMPGTW MM0,MM1

;   PMADDwd MM0,MM1
   MOVQ  MM0, QWORD PTR X
   PADDB   MM0, QWORD PTR Y 
   MOVQ  QWORD PTR Z,  MM0
   invoke ExitProcess, 0
END START