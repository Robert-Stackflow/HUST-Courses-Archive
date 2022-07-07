.386
STACK	segment USE16 STACK		;主程序堆栈段
		DB 200 DUP(0)
STACK   ENDS
;数据段
DATA	SEGMENT USE16
		STR1	    DB	'FIRST INSTALLING! $'     	;'$'结束字符串
		STR2		DB	'INSTALLED! $'     			;'$'结束字符串
DATA	ENDS
;代码段
CODE	SEGMENT USE16
		ASSUME	CS:CODE,DS:CODE,SS:STACK
		COUNT	DB	18
		HOUR	DB	?,?,':'
		MIN		db	?,?,':'
		SEC		DB	?,?
		BUF_LEN = $ - HOUR	 	;显示的信息长度
		CURSOR	DW	?			;原光标位置
		OLD_INT	DW	00E0H,0F100H	;原INT 08H的中断矢量
NEW08H	PROC	FAR
		PUSHF
		CALL	DWORD PTR CS:OLD_INT	;完成原有的中断处理程序(变量在汇编后使用的默认段寄存器为DS，故必须加段前缀CS)
		DEC		CS:COUNT				;计数
		JZ		DISP	 				;计满18次，转时钟显示
		IRET							;未满18次，中断返回
DISP:	MOV		CS:COUNT,18				;重置计数初值
		STI								;打开中断
		PUSHA	 						;保护现场
		PUSH	DS
		PUSH	ES
		MOV		AX,CS	 				;令DS,ES指向CS段
		MOV		DS,AX
		MOV		ES,AX
		CALL	GET_TIME				;获取当前时间
		MOV		BH,0
		MOV		AH,3
		INT		10H						;读取光标信息，调用参数为AH表示指令，BH表示显示的页码，出口参数为CH=光标起始行，CL=光标终止行，DH=行/Y坐标，DL=列/X坐标
		MOV		CURSOR,DX	 			;CURSOR保存原光标位置
		MOV		BP,OFFSET HOUR			;ES:[BP]指向显示信息的起始地址
		MOV		BH,0	 				;显示页码为0
		MOV		DH,0	 				;显示行数为0
		MOV		DL,80 - BUF_LEN			;显示列数设置
		MOV		BL,07H					;包含显示属性
		MOV		CX,BUF_LEN				;显示的字符串长度
		MOV		AL,0					;指定显示输出方式——显示后，光标位置不变
		MOV		AH,13H					;调用显示字符串的功能
		INT		10H
		MOV		BH,0					;对0号页码操作
		MOV		DX,CURSOR	 			;指定原光标位置
		MOV		AH,2	 				;调用功能编号
		INT		10H						;恢复原光标位置
		POP		ES
		POP		DS
		POPA	 						;恢复现场
		IRET	 						;中断返回
NEW08H  ENDP
GET_TIME PROC
		;取出"时钟"信息
		MOV		AL,4
		OUT		70H,AL
		JMP		$+2
		IN		AL,71H
		MOV		AH,AL 					;扩展BCD码
		AND		AL,0FH
		SHR		AH,4
		ADD		AX,3030H	 			;转换为ASCII码
		XCHG	AH,AL	 				;高低位交换
		MOV		WORD PTR HOUR , AX	 	;存储内容至显示信息的字节中
		;取出"分钟"信息
		MOV		AL,2
		OUT		70H,AL
		JMP		$+2
		IN		AL,71H
		MOV		AH,AL
		AND		AL,0FH
		SHR		AH,4
		ADD		AX,3030H
		XCHG	AH,AL
		MOV		WORD PTR MIN,AX
		;取出"秒钟"信息
		MOV		AL,0
		OUT		70H,AL
		JMP		$+2
		IN		AL,71H
		MOV		AH,AL
		AND		AL,0FH
		SHR		AH,4
		ADD		AX,3030H
		XCHG	AH,AL
		MOV		WORD PTR SEC,AX
		RET
GET_TIME ENDP
;初始化(中断处理程序的安装)及主程序
BEGIN:	PUSH	CS
		POP		DS
		MOV		AX,3508H				;获取原08H的中断向量，调用参数为中断类型号为AL，返回参数为ES:BX=中断向量
		INT		21H
		;;;;判断是否已安装中断处理程序
		CMP		BX,OLD_INT
		JNE		INSTALLED				;若BX与OLD_INT对应BX不相等，不相等说明已安装
		mov     AX,ES
		cmp		AX,OLD_INT+2
		JNE		INSTALLED				;若ES与OLD_INT对应ES不相等，说明已安装
		MOV		OLD_INT,BX
		MOV		OLD_INT+2,ES 			;将ES:BX保存至OLD_INT中(保存中断矢量)
		MOV		DX,OFFSET NEW08H
		MOV		AX,2508H				;设置新的08H中断向量，调用参数为DS:DX=中断向量，AL=中断类型号
		INT		21H
NEXT:	;MOV		AH,0	 				;从键盘读入字符送AL寄存器
		;INT		16H						;等待按键
		;CMP		AL,'q'
		;JNE		NEXT
		MOV 	AX, DATA
		MOV 	DS, AX	 				;DS指向DATA段以取出字符串
		LEA 	DX, STR1				;DX表示待打印信息MEASSGAE的偏移地址
		MOV 	AH, 9H					;显示字符串，调用参数为DS:DX=串地址，其中'$'结束字符串
		INT 	21H
		JMP 	INTERRUPT
INSTALLED:
		MOV 	AX, DATA
		MOV 	DS, AX	 				;DS指向DATA段以取出字符串
		LEA 	DX, STR2				;DX表示待打印信息MEASSGAE的偏移地址
		MOV 	AH, 9H					;显示字符串，调用参数为DS:DX=串地址，其中'$'结束字符串
		INT 	21H
INTERRUPT:
		MOV 	DX, OFFSET BEGIN +15 	;计算中断处理程序的字节数, +15以便于在计算节数时向上取整
		MOV 	CL, 4
		SHR 	DX, CL					;每节代表16个字节，将字节数转换为节数
		ADD 	DX, 50H					;设置驻留区大小，需包括程序段前缀的内容(50H个字节)
		MOV 	AL, 0 					;设置返回码为0
		MOV 	AH, 31H					;结束并驻留，调用参数为AL=返回码，DX=驻留区大小，退出时,将(DX)节的主存单元驻留(不释放)
		INT 	21H
CODE	ENDS
		END	BEGIN