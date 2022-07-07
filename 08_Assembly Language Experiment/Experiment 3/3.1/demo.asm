.686P
.model flat, stdcall
 ExitProcess proto stdcall:dword
 includelib  kernel32.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
 printf PROTO C :VARARG
 scanf	PROTO C :VARARG
 getchar PROTO  C:VARARG
 calculate  proto
 copy       proto
 display    proto

 include struct.asm

cmpstr macro flag,str1,str2
	local L1, L2, L3, exit
	push ecx
	push edx
	xor ecx, ecx
L1:
	cmp str1[ecx], 0
	je L2
	mov dl, str1[ecx]
	cmp dl, str2[ecx]
	jnz L3
	inc ecx
	jmp L1
L2:
	cmp str2[ecx], 0
	jnz L3
	mov flag, 1
	jmp exit
L3:
	mov flag, 0
	jmp exit
exit:
	pop edx
	pop ecx
endm

 public LOWF,MIDF,HIGHF,stream,indexLOW,indexMID,indexHIGH,numofTest,printTupleBuf,printBuf,calculateTip,displayTip

.DATA
  printBuf						db  "%s",0ah,0dh,0
  printTupleBuf					db  "%d,%d,%d",0ah,0dh,0
  scanBuf						db  "%s",0
  inputOrderTip					db  '>>Input your option(R|Q):',0
  usernameTip					db  '>>Input your username:',0
  usernameNotFoundTip			db  'User not found!',0
  passwordTip					db  '>>Input your password:',0
  passwordWrongTip              db  'Incorrect password!',0
  successTip					db  'Logged in!',0
  calculateTip                  db  'Calculating the tuples...',0
  displayTip					db  'The tuples in the MIDF:',0
  defaultUsername               db  'xuruida',0
  defaultPassword               db  '123456',0
  inputPasswordTime             dd  0
  usernameFlag                  dd  0
  passwordFlag                  dd  0
  LOWF							tuple 6 DUP(<0, 0, 0>)
  MIDF							tuple 6 DUP(<0, 0, 0>)
  HIGHF							tuple 6 DUP(<0, 0, 0>)
  stream						tuple <250000,-1024,1300>
								tuple <1,2,3>
								tuple <2560,0,100>
								tuple <25000, 30000, 7000>
								tuple <-10110, -9333, 5678>
								tuple <-12400, 29234, 9543>
  indexLOW						dd  0
  indexMID						dd  0
  indexHIGH						dd  0
  numofTest						dd  0
  inputUsername					db  0
  inputPassword					db  0
  inputOrder					db  0
.STACK 200
.CODE
main proc c
USERLOOP:
			invoke printf,offset printBuf,offset usernameTip
			invoke scanf,offset scanBuf,offset inputUsername
			cmpstr usernameFlag,defaultUsername,inputUsername
			cmp usernameFlag,1
		    je PASSWORDLOOP
			invoke printf,offset printBuf,offset usernameNotFoundTip
			jmp USERLOOP
PASSWORDLOOP:
			invoke printf,offset printBuf,offset passwordTip
			invoke scanf,offset scanBuf,offset inputPassword
			cmpstr passwordFlag,defaultPassword,inputPassword
			cmp passwordFlag,1
			jz RIGHT
			inc inputPasswordTime
			.if inputPasswordTime < 3
				invoke printf,offset printBuf,offset passwordWrongTip
				jmp PASSWORDLOOP
			.else
				jmp EXIT
			.endif
RIGHT:
			invoke copy
			invoke display
ORDERLOOP:
			invoke printf,offset printBuf,offset inputOrderTip
			invoke scanf,offset scanBuf,offset inputOrder
			cmp inputOrder,52H
			jz RIGHT
			cmp inputOrder,51H
			jz EXIT
			jmp ORDERLOOP
EXIT:
			invoke Exitprocess,0
main endp
END