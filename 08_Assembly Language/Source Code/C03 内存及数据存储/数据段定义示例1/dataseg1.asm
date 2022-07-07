.686P
.model flat, stdcall
  ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
 includelib  libcmt.lib   
 includelib  legacy_stdio_definitions.lib
.data
  x  db  10,20,30
  y  dw  10,20,30
  z  dd  10,20,30
  u  db  '12345'
  p  dd  X, Y
  q  db  2 DUP (5), 3 DUP (4)
.stack 200
.code
main proc c
    invoke ExitProcess, 0
main endp
end