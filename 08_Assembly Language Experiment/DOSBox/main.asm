.386
STACK	segment USE16 STACK
		DB 200 DUP(0)
STACK   ENDS
;数据段
DATA	SEGMENT USE16
		TIP		DB	'ENROLLED $'
DATA	ENDS
;代码段
CODE	SEGMENT USE16
		ASSUME	CS:CODE,DS:CODE,SS:STACK
		COUNT	DB	18
		HOUR	DB	?,?,':'
		MIN		db	?,?,':'
		SEC		DB	?,?
		BUF_LEN = $ - HOUR
		CURSOR	DW	?
		OLDBX	DW	00E0H
		OLDES   DW  0F100H
		OLD_INT DW  ?,?
NEW08H	PROC	FAR
		PUSHF
		CALL	DWORD PTR CS:OLD_INT
		DEC		CS:COUNT
		JZ		DISP
		IRET
DISP:	MOV		CS:COUNT,18
		STI
		PUSHA
		PUSH	DS
		PUSH	ES
		MOV		AX,CS
		MOV		DS,AX
		MOV		ES,AX
		CALL	GET_TIME
		MOV		BH,0
		MOV		AH,3
		INT		10H
		MOV		CURSOR,DX
		MOV		BP,OFFSET HOUR
		MOV		BH,0
		MOV		DH,0
		MOV		DL,80 - BUF_LEN
		MOV		BL,07H
		MOV		CX,BUF_LEN
		MOV		AL,0
		MOV		AH,13H
		INT		10H
		MOV		BH,0
		MOV		DX,CURSOR
		MOV		AH,2
		INT		10H
		POP		ES
		POP		DS
		POPA
		IRET
NEW08H  ENDP
GET_TIME PROC
		MOV		AL,4
		OUT		70H,AL
		JMP		$+2
		IN		AL,71H
		MOV		AH,AL
		AND		AL,0FH
		SHR		AH,4
		ADD		AX,3030H
		XCHG	AH,AL
		MOV		WORD PTR HOUR , AX
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
BEGIN:	PUSH	CS
		POP		DS
		MOV		AX,3508H
		INT		21H
		CMP		BX,OLDBX
		JNE		ENROLLED
		mov     AX,ES
		cmp		AX,OLDES
		JNE		ENROLLED
		MOV		OLD_INT,BX
		MOV		OLD_INT+2,ES
		MOV		DX,OFFSET NEW08H
		MOV		AX,2508H
		INT		21H
NEXT:	MOV		AH,0
		INT		16H
		CMP		AL,'q'
		JNE		NEXT
		JMP 	EXIT
ENROLLED:
		MOV 	AX, DATA
		MOV 	DS, AX
		LEA 	DX, TIP
		MOV 	AH, 9H
		INT 	21H
EXIT:
		MOV 	DX, OFFSET BEGIN +15
		MOV 	CL, 4
		SHR 	DX, CL
		ADD 	DX, 20H
		MOV 	AL, 0
		MOV 	AH, 31H
		INT 	21H
CODE	ENDS
		END	BEGIN