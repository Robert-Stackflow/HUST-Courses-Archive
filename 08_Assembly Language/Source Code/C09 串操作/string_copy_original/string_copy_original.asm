.686P
.model flat, c
  ExitProcess  proto stdcall :DWORD
;  includelib   msvcrt.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf       proto :ptr sbyte, :vararg
  clock        proto 
  getchar      proto 
.data
  lpFmt	    db	"%d (ms)", 0dh,0ah,0
  buf1        db   10000 dup(0)
  buf2        db   10000 dup(1)
  begin_time  dd   0
  end_time    dd   0
  spend_time  dd   0         ; 运行时间(豪秒)
.stack 200
.code
main  proc
   invoke clock
   mov    begin_time, eax
   mov    ebx, 20000
L:
   lea    esi, buf1
   lea    edi, buf2
   mov    ecx, 10000
   cld
   rep    movsb
   dec    ebx
   jnz    L
   invoke clock
   mov    end_time, eax
   sub    eax, begin_time
   mov    spend_time, eax
   invoke printf,offset lpFmt, spend_time
   invoke getchar
   invoke ExitPRocess, 0
main  endp
END