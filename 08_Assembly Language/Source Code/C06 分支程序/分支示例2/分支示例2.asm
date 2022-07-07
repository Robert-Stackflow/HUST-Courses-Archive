.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
;  includelib      msvcrt.lib
  printf          PROTO C :ptr sbyte, :VARARG
    includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
.DATA
  lpFmt	db	"x=%d y=%d R=%d",0ah, 0dh, 0
  X  DD  5
  Y  DD  6
  R  DD  0
.STACK 200
.CODE
main  proc  c 
   CMP  X, 0
   JS   X_Negative
         ; 此处向下是  X>=0 的情况
   CMP  Y, 0 
   JS   @F
   MOV  R, 1
   JMP  EXIT
@@:
   MOV  R, 0
   JMP  EXIT
         ; 至此，X>=0 的情况处理结束
		 ; 以下是 X<0的情况
X_Negative:
   CMP Y, 0
   JS  @F
   MOV R, 0
   JMP EXIT
@@:
   MOV  R,-1
EXIT:
   invoke printf,offset lpFmt,X,Y,R
   invoke ExitProcess, 0
main  endp
end