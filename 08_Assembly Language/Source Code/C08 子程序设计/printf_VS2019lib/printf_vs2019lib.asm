.686P
.model flat, stdcall
option casemap:none

includelib libcmt.lib
includelib libvcruntime.lib
includelib libucrt.lib
includelib legacy_stdio_definitions.lib

ExitProcess PROTO return:DWORD
;extern printf:NEAR
printf PROTO C :vararg
.data
text BYTE "Text %d", 0


.code
main PROC C                    ; Specify "C" calling convention
;    push  120
;    push offset text
;   call printf
 ;  add  esp, 4	
   invoke printf, offset text,120
 
;   invoke ExitProcess,0       ; Since the C library called main (this function)
                               ; we can set eax to 0 and use ret`to have
                               ; the C runtime close down and return our error
                               ; code instead of invoking ExitProcess
    mov eax, 0
    ret
main ENDP
end                            ; Use `end` on a line by itself
                               ; We don't want to use `end main` as that would
                               ; make this function our program entry point
                               ; effectively skipping by the C runtime initialization