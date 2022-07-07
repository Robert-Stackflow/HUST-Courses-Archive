.686P
.model flat,stdcall
OPTION CASEMAP:NONE

WinMain proto :DWORD
WndProc proto :DWORD,:DWORD,:DWORD,:DWORD
Convert proto :BYTE,:DWORD
include windows.inc
include user32.inc
include kernel32.inc
include gdi32.inc

.data
szClassName  db "TryWinClass",0
szTitle      db " First Window",0
hInstance    DD 0
szDisplayStr DB  "The ASCII of char '?' is:  "
szASCII      DB  "00H",20H,20H
dwDisplayLength   DD   $-szDisplayStr

.code
START:
	invoke GetModuleHandle,NULL
	mov    hInstance,eax
	invoke WinMain,hInstance
	invoke ExitProcess,eax

;**************
WinMain proc hInst:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
    invoke RtlZeroMemory,addr wc,SIZEOF wc
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, offset WndProc
    mov   wc.cbClsExtra,NULL
	mov   wc.cbWndExtra,NULL
	push  hInst
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_WINDOW+1
	mov   wc.lpszMenuName,NULL
	mov   wc.lpszClassName,offset szClassName
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,0
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	invoke RegisterClassEx, addr wc
	invoke CreateWindowEx,NULL,ADDR szClassName,ADDR szTitle,
           WS_OVERLAPPEDWINDOW,
		   CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,\
		   NULL,NULL,hInst,NULL

	mov   hwnd,eax
	invoke ShowWindow, hwnd,SW_SHOWNORMAL
	invoke UpdateWindow, hwnd
StartLoop:
    invoke GetMessage,ADDR msg,NULL,0,0
    cmp  eax,0
    je   ExitLoop
    invoke TranslateMessage, ADDR msg
    invoke DispatchMessage, ADDR msg
	jmp StartLoop 
ExitLoop:
     mov  eax,msg.wParam
	 ret
WinMain ENDP

;*************************
WndProc proc hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
  LOCAL hdc:HDC
.IF uMsg==WM_DESTROY
     invoke PostQuitMessage,NULL
 .ELSEIF uMsg==WM_CHAR
      invoke GetDC,hWnd
      mov    hdc,eax
      mov    eax,wParam
      mov    szASCII-8,al
      invoke  Convert,al,ADDR szASCII
      invoke TextOut,hdc,40,40,ADDR szDisplayStr,dwDisplayLength
 .ELSE
      invoke DefWindowProc,hWnd,uMsg,wParam,lParam
      ret
 .ENDIF
  xor    eax,eax
  ret
WndProc endp

;**********************
Convert  PROC bChar:BYTE,lpStr:DWORD
         push esi
         push eax
         mov  al,bChar
         mov  esi,lpStr
         shr  al,4
         cmp  al,10
         jb   L1
         add  al,7
L1:      add  al,30H
         mov  [esi],al
         mov  al,bChar
         and  al,0FH
         cmp  al,10
         jb   L2
         add  al,7
L2:      add  al,30H
         mov  [esi+1],al
         pop  eax
         pop  esi
         ret
Convert  ENDP
END  START
