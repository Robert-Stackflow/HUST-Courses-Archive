;----------------------------
STACK	SEGMENT STACK
	DB	200 DUP(0)
STACK	ENDS
;----------------------------
DATA	SEGMENT
hello	DB	'How are you! $'
DATA	ENDS
;------------------------------
CODE SEGMENT
        ASSUME CS:CODE,DS:DATA,SS:STACK
BEGIN:	MOV AX,DATA
	MOV DS,AX
	LEA DX,hello
	MOV ah,9     ;display
        int 21h       
	MOV AH,4CH   ;exit
	INT 21H
;-----------------------------
CODE	ENDS
	END BEGIN