; 80X86汇编语言程序设计  P266-270
; 显示一个窗口
; 用户按一个键后，显示该键的ASCII

.386
.model FLAT,STDCALL
OPTION CASEMAP:NONE

WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc proto :DWORD,:DWORD,:DWORD,:DWORD
Convert proto :BYTE,:DWORD

; include asm_API.inc
 ;include asm_STRUCT.inc

include windows.inc
include user32.inc
include kernel32.inc
include gdi32.inc
;includelib user32.lib
;includelib gdi32.lib
;includelib kernel32.lib

.data
ClassName    db "TryWinClass",0
AppName      db "Our First Window",0
hInstance    DD 0
CommandLine  DD 0
OurText      db  "These words are printed in the window!"
num1         DD   $-OurText
OurStr       DB  "The ASCII of char '?' is: ",20H
szASCII      DB  "00H",20H,20H
num2         DD   $-OurStr
NumTable     DB  "0123456789ABCDEF"

.code
START:
	invoke GetModuleHandle,NULL
	mov    hInstance,eax
	invoke GetCommandLine
	mov CommandLine,eax
	invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	invoke ExitProcess,eax

;**************
WinMain proc hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
        invoke RtlZeroMemory,ADDR wc,SIZEOF wc
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	mov   wc.cbClsExtra,NULL
	mov   wc.cbWndExtra,NULL
	push  hInst
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_WINDOW+1
	mov   wc.lpszMenuName,NULL
	mov   wc.lpszClassName,OFFSET ClassName
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	mov   wc.hIconSm,0
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	invoke RegisterClassEx, ADDR wc
	INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
           WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
           CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
           hInst,NULL
	mov   hwnd,eax
	INVOKE ShowWindow, hwnd,SW_SHOWNORMAL
	INVOKE UpdateWindow, hwnd

; ************************************	
	invoke GetDC,hwnd
        invoke TextOut,eax,10,15,offset OurText,num1
;*************************************
StartLoop:
                INVOKE GetMessage,ADDR msg,NULL,0,0
                cmp  EAX,0
                JE   ExitLoop
                INVOKE TranslateMessage, ADDR msg
                INVOKE DispatchMessage, ADDR msg
	            JMP StartLoop 
ExitLoop:
       	 mov  eax,msg.wParam
	 RET
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
      mov    szASCII-8,AL
      invoke  Convert,AL,ADDR szASCII
      invoke TextOut,hdc,10,15,ADDR OurText,num1
      invoke TextOut,hdc,40,40,ADDR OurStr,num2
 .ELSE
      invoke DefWindowProc,hWnd,uMsg,wParam,lParam
      ret
 .ENDIF
  xor    eax,eax
  ret
WndProc endp

;**********************
Convert  PROC bChar:BYTE,lpStr:DWORD
         PUSH ESI
         PUSH EAX
         MOV  AL,bChar
         MOV  ESI,lpStr
         SHR  AL,4
         CMP  AL,10
         JB   L1
         ADD  AL,7
L1:      ADD  AL,30H
         MOV  [ESI],AL
         MOV  AL,bChar
         AND  AL,0FH
         CMP  AL,10
         JB   L2
         ADD  AL,7
L2:      ADD  AL,30H
         MOV  [ESI+1],AL
         POP  EAX
         POP  ESI
         RET
Convert  ENDP

         
		 END  START
