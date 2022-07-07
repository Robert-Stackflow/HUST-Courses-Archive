.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
  printf          PROTO C :ptr sbyte, :VARARG
  scanf_s         PROTO C :ptr sbyte, :VARARG
  includelib      libcmt.lib
  includelib    legacy_stdio_definitions.lib

.DATA
  lpFmt	db	"%19s",0
  str1  db  20 dup(0)
  str2  db  20 dup(0)
  x     dd  5 dup(0)
  STRINGSTAB  db 'good',0,(10+STRINGSTAB-$) dup(0)
              db 'hello',0,(20+STRINGSTAB-$) dup(0)
			  db 'asm',0,(30+STRINGSTAB-$) dup(0)
.STACK 200
.CODE
main proc c
   invoke scanf_s, offset lpFmt,  offset str1,20

   invoke scanf_s, offset lpFmt,  offset str2,20
 
   invoke printf,offset lpFmt,offset str1
   invoke ExitProcess, 0
main endp
END