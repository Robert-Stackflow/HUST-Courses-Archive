.686P
.model flat, C
;  includelib      msvcrt.lib
  printf          PROTO :VARARG

extern  lpFmt:sbyte

.CODE
; SORT ：对一个双字类型的数组按从小到大的顺序排序
; BUF  : 输入缓冲区的首地址，也是排序结果存放的首地址
; NUM  : 元素的个数
SORT  PROC BUF:DWORD, NUM:DWORD
   LOCAL   OUTLOOP_NUM:DWORD
   .IF (NUM<2)
       RET
   .ENDIF
   MOV  EAX, NUM
   DEC  EAX
   MOV  OUTLOOP_NUM, EAX  ; 外循环的次数
   MOV  EBX, BUF  ; 数据缓冲区的首地址在 EBX中
   MOV  ESI, 0    ; 外循环的控制指针
Out_Loop:    ; 外循环
   CMP  ESI, OUTLOOP_NUM
   JAE  EXIT
              ; 下面是内循环
   LEA  EDI, [ESI+1]
   Inner_Loop:
         CMP  EDI, NUM
		 JAE  Inner_Loop_Over
		 MOV  EAX, [EBX][ESI*4]
		 CMP  EAX, [EBX][EDI*4]
		 JLE  Inner_Modify
		 XCHG EAX, [EBX][EDI*4]
		 MOV  [EBX][ESI*4], EAX
	Inner_Modify:   ; 修改内循环的控制变量
	     INC  EDI
		 JMP  Inner_Loop
	Inner_Loop_Over:
	INC  ESI
	JMP  Out_Loop
EXIT:
	RET
SORT ENDP

DISPLAY PROC BUF:DWORD, NUM:DWORD
	MOV  ECX,NUM
	MOV  EBX, BUF
   .WHILE (NUM>0)
    invoke printf,offset lpFmt, DWORD PTR [EBX]
	ADD  EBX,4
	DEC  NUM
   .ENDW
   RET
DISPLAY ENDP
END 

