.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib  

;  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG

.DATA
  lpFmt	db	"x=%d y=%d R=%d",0ah, 0dh, 0
  X  SDWORD  -5
  Y  SDWORD  6
  R  DD  0
.STACK 200
.CODE

main  proc  c
   .if ((X>=0) || (X==5))
       .if  Y>=0
	       MOV  R, 1
	   .else
	       MOV  R, 0
	   .endif
	.else
       .if  Y>=0
	       MOV  R, 0
	   .else
	       MOV  R, -1
	   .endif
	.endif

   invoke printf,offset lpFmt,X,Y,R
   invoke ExitProcess, 0
main  endp
end