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
  ;采用与密码串依次异或的方法加密用户名，长度为7
  defaultUsername               db  'x' XOR 'A'
  								db  'u' XOR 'A'
  								db  'r' XOR 'A'
  								db  'u' XOR 'A'
  								db  'i' XOR 'A'
  								db  'd' XOR 'A'
  								db  'a' XOR 'A',0
  ;采用函数(X-21H)*7的方法加密密码，同时使用随机字符填充密码，长度为10
  defaultPassword				db  ('d'-21H)*3
  								db  ('a'-21H)*3
								db  ('r'-21H)*3
								db  ('l'-21H)*3
								db  ('i'-21H)*3
								db  ('n'-21H)*3
								db  ('g'-21H)*3
								db  12H,34H,56H
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
  mode                          dd  0
  inputUsername					db  10 dup(0)
  inputPassword					db  10 dup(0)
  inputOrder					db  10 dup(0)

.STACK 200
.CODE
main proc c
USERLOOP:
			invoke printf,offset printBuf,offset usernameTip
			invoke scanf,offset scanBuf,offset inputUsername
			mov mode,0
			push mode
			push offset inputUsername
			call cmpstr
			;采用与密码串依次异或的方法加密用户名，长度为7
			username			db  'x' XOR 'A'
  								db  'u' XOR 'A'
  								db  'r' XOR 'A'
  								db  'u' XOR 'A'
  								db  'i' XOR 'A'
  								db  'd' XOR 'A'
  								db  'a' XOR 'A',3 DUP(0)
			cmp  eax,1
		    je PASSWORDLOOP
			invoke printf,offset printBuf,offset usernameNotFoundTip
			jmp USERLOOP
PASSWORDLOOP:
			invoke printf,offset printBuf,offset passwordTip
			invoke scanf,offset scanBuf,offset inputPassword
			mov mode,1
			push mode
			push offset inputPassword
			call cmpstr
			;采用函数(X-21H)*7的方法加密密码，同时使用随机字符填充密码，长度为10
			password			db  ('d'-21H)*3
  								db  ('a'-21H)*3
								db  ('r'-21H)*3
								db  ('l'-21H)*3
								db  ('i'-21H)*3
								db  ('n'-21H)*3
								db  ('g'-21H)*3,3 DUP(0)
			cmp eax,1
			jz RIGHT
			inc inputPasswordTime
			cmp inputPasswordTime,3
			jz  EXIT
			invoke printf,offset printBuf,offset passwordWrongTip
			jmp PASSWORDLOOP
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
cmpstr proc
	pop  edi
	push ebp
	mov  ebp, esp
	mov  esi, [ebp + 4]
	mov  edx, [ebp + 8]
	push edi
	cmp  edx,0
	je   usernameJudge
	jne  passwordJudge
usernameJudge:
	mov  al, [edi]
	mov  dl, [esi]	
	cmp  al, 0
	je   terminal
	xor  dl,'A'
	cmp  al,dl
	jne  wrong
	inc  edi
	inc  esi
	jmp  usernameJudge
	trueUsername db 'daruixu',0
passwordJudge:
	mov  al, [edi]
	mov  dl, [esi]	
	cmp  al, 0
	je   terminal
	sub  dl,21H
	mov  dh,0
	imul dx,3
	cmp  al,dl
	jne  wrong
	inc  edi
	inc  esi
	jmp  passwordJudge
	truePassword db 'asdfgh',0
terminal:
	cmp  dl, 0
	jnz  wrong
	mov  eax, 1
	jmp  exit
wrong:
	mov  eax, 0
exit:
	pop edi
    add  edi,10
	pop  ebp
	push edi
	ret
cmpstr endp
END