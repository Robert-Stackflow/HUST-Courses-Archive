.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  ; includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib 

.DATA
  lpFmt	db	"x=%d y=%d R=%d",0ah, 0dh, 0
  X  DD  -5
  Y  DD  6
  R  DD  0
  count  DD 26 dup(0)
  buf  db 'abcdabb',0
.STACK 200
.CODE
main proc c
   MOV R,0
   .switch x
      .case 1 : 
	     mov Y,1
	  .case 2 :
	     mov Y,2
		 .default:
		 mov y,3
		 .endswitch
  

   exit:
   invoke ExitProcess, 0
main  endp
END