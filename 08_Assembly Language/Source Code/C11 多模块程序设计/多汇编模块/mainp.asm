
.686P
.model flat, C
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
 ; includelib      msvcrt.lib
  includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf          PROTO  :VARARG
  getchar         PROTO
  SORT     PROTO  :DWORD, :DWORD
  DISPLAY PROTO  :DWORD, :DWORD
  PUBLIC  lpFmt

.DATA
  lpFmt	DB	"%d ", 0
  CRLF  DB  0DH,  0AH, 0
  BUF1  SDWORD   -10, 20, 30,-100, 25, 60
  N1    DWORD  ($-BUF1)/4
  BUF2  SDWORD   -70, 55, 200,-150, 125, 90,-50
  N2    DWORD  ($-BUF2)/4

.STACK 200
.CODE
main PROC
   INVOKE  SORT, OFFSET BUF1, N1
   INVOKE  SORT, OFFSET BUF2, N2
   ;INVOKE  SORT_PESUDO, OFFSET BUF1, N1
   ;INVOKE  SORT_PESUDO, OFFSET BUF2, N2
   INVOKE  DISPLAY, OFFSET BUF1, N1
   invoke printf,offset CRLF

   INVOKE  DISPLAY, OFFSET BUF2, N2
   INVOKE  getchar
   invoke ExitProcess, 0
main  ENDP
END