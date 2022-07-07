.686P
.model flat, c
  ExitProcess proto stdcall :dword
  includelib  kernel32.lib
   includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf      proto :ptr sbyte, :vararg
.data
  lpFmt	   db	"%d ", 0dh,0ah,0
.stack 200
.code
 myfadd  proc   c, x:dword,  y:dword
       local u:dword,v:dword,w:dword
	   mov   eax, x
	   add   eax, 10
	   mov   u,   eax    ; u=x+10;
	   mov   eax, y
	   add   eax, 25
	   mov   v,   eax    ; v=y+25;
	   add   eax, u
	   mov   w,   eax    ; w=u+v;
	   ret
myfadd   endp
main proc
     local  a:dword,b:dword,sum:dword
     mov   a, 100
mov   b, 200
    invoke myfadd, a, b
	 mov   sum, eax
     invoke printf,offset lpFmt, sum
     invoke ExitProcess, 0
	 ret
main  endp
end
