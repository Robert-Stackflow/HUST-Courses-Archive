.686P
.model flat, C
public y
public SORT_PESUDO
printf proto c  :vararg

.DATA
  y  SDWORD 300
  lpfmt db '%s',0dh,0ah,0
  msg   db 'good in asm',0
.CODE

; SORT ：对一个双字类型的数组按从小到大的顺序排序
; BUF  : 输入缓冲区的首地址，也是排序结果存放的首地址
; NUM  : 元素的个数

SORT_PESUDO  PROC BUF:DWORD, NUM:DWORD
   LOCAL   OUTLOOP_NUM:DWORD
   invoke printf, offset lpfmt,offset msg
   .IF (NUM<2)
       RET
   .ENDIF
   MOV  EAX, NUM
   DEC  EAX
   MOV  OUTLOOP_NUM, EAX  ; 外循环的次数
   MOV  EBX, BUF  ; 数据缓冲区的首地址在 EBX中
   MOV  ESI, 0    ; 外循环的控制指针
   .WHILE (ESI < OUTLOOP_NUM)
              ; 下面是内循环
       LEA  EDI, [ESI+1]
	   MOV  EAX, [EBX][ESI*4]
       .WHILE (EDI < NUM) 
		   .IF   EAX >= SDWORD PTR [EBX][EDI*4]
		         XCHG EAX, [EBX][EDI*4]
		   .ENDIF
	       INC  EDI
	 .ENDW
	 MOV  [EBX][ESI*4],EAX
	 INC  ESI
   .ENDW
   RET
SORT_PESUDO ENDP

extern x:sdword
modify_in_asm  PROC 
   mov  x,   100
   mov  x[1*TYPE SDWORD],200
   RET
modify_in_asm ENDP

END 

