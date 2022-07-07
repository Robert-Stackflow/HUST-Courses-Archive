extern "C" printf:proc
.DATA
 lpFmt	db	"This Message",0ah, 0dh, 0
 lpFmt1	db	"This Message 123",0ah, 0dh, 0
 X      DB  0FFH,0FFH
 dv    real8 3.4

.CODE
 mainp PROC
    mov   rcx, offset lpFmt

   call printf

       mov   rcx, offset lpFmt1

   call printf
    ret
mainp endp
end