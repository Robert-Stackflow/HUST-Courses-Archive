.686P 
.model flat,c
 ExitProcess proto  stdcall :dword
 includelib  kernel32.lib
 printf      proto c :vararg
 includelib  libcmt.lib   
 includelib  legacy_stdio_definitions.lib
.data
 lpFmt	db	"%d",0ah, 0dh, 0
.stack 200
.code
main proc  
    ; eax=0; for (ebx=1;ebx<=100;ebx++) eax=eax+ebx;
   mov  eax, 0
   mov  ebx, 1
lp: cmp  ebx, 100
   jg   exit
   add  eax, ebx
   inc  ebx
   jmp  lp
exit:
   invoke printf,offset lpFmt,eax
   invoke ExitProcess, 0
main endp
end 