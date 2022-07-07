.686
.model FLAT,STDCALL
OPTION CASEMAP:NONE

WinMain proto :DWORD
WndProc proto :DWORD,:DWORD,:DWORD,:DWORD
DialogProc proto :DWORD,:DWORD,:DWORD,:DWORD
include windows.inc
include user32.inc
include kernel32.inc
include gdi32.inc
include resource.inc

.data
szClassName       db "MenuDialogTest",0
szTitle           db " Menu Dialog Test Window",0
hInstance         dd  0
szMessageBoxTitle db "Message Box Title",0
szMessageConfirm db "Are you sure to close the window ?",0
szAuthorInfo      db "Author : Xu Xiang Yang",0
szVersionInfo     db "Version : 1.0",0
szInputText       db  100 dup(0)
dwInputLength dd  0
szCancelPress     db "Cancel Button is pressed ",0
dwCancelPressLength = $ - szCancelPress -1
szClosePress      db  " Close Window is pressed. ",0
dwClosePressLength = $ - szClosePress -1
szClearText       db  100 dup(' ')

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
	LOCAL hMenu:HMENU
    invoke RtlZeroMemory,ADDR wc,SIZEOF wc
	mov   wc.cbSize,SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	push  hInst
	pop   wc.hInstance
	mov   wc.hbrBackground,COLOR_WINDOW+1
	mov   wc.lpszClassName,OFFSET szClassName
	invoke LoadIcon,NULL,IDI_APPLICATION
	mov   wc.hIcon,eax
	invoke LoadCursor,NULL,IDC_ARROW
	mov   wc.hCursor,eax
	invoke RegisterClassEx, ADDR wc
	invoke LoadMenu, hInst, IDM_MYMENU
	mov    hMenu,eax
	invoke CreateWindowEx,NULL,ADDR szClassName,ADDR szTitle,\
           WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
           CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,hMenu,\
           hInst,NULL
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
  LOCAL x:DWORD
.IF uMsg == WM_COMMAND
   .IF wParam == ID_OP_OPEN
       invoke DialogBoxParam,NULL,IDD_MY_DIALOG,hWnd,offset DialogProc,NULL
       invoke GetDC,hWnd
       mov    hdc,eax
	   invoke TextOut,hdc,40,40,addr szClearText,100
       invoke TextOut,hdc,40,40,addr szInputText,dwInputLength
   .ELSEIF  wParam == ID_OP_EXIT
       invoke DestroyWindow, hWnd
;	   invoke PostQuitMessage,NULL
   .ELSEIF  wParam == ID_HELP_VERSION
       invoke MessageBox, hWnd,addr szVersionInfo, addr szMessageBoxTitle,MB_OK
   .ELSEIF  wParam == ID_HELP_AUTHOR
       invoke MessageBox, hWnd,addr szAuthorInfo, addr szMessageBoxTitle,MB_OK
   .ENDIF
.ELSEIF uMsg==WM_CLOSE
      invoke MessageBox, hWnd,addr szMessageConfirm, addr szMessageBoxTitle,MB_YESNO
	  .if  eax == IDYES
           invoke DestroyWindow, hWnd
	  .endif
.ELSEIF uMsg==WM_DESTROY
      invoke PostQuitMessage,NULL
 .ELSE
      invoke DefWindowProc,hWnd,uMsg,wParam,lParam
      ret
 .ENDIF
  xor    eax,eax
  ret
WndProc endp

DialogProc proc hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
LOCAL  hEdit:DWORD
.IF uMsg == WM_CLOSE
     invoke	wsprintf, addr szInputText, addr szClosePress
   	 mov  dwInputLength, dwClosePressLength  
     invoke  EndDialog, hWnd, NULL
.ELSEIF uMsg == WM_COMMAND
   .IF wParam == IDOK
       invoke GetDlgItem, hWnd,IDC_MYDIALOG_EDIT
	   mov hEdit, eax
	   invoke GetWindowTextLength,hEdit
	   mov dwInputLength, eax  
       invoke GetDlgItemText, hWnd,IDC_MYDIALOG_EDIT, offset szInputText,100
       invoke EndDialog,hWnd,NULL
   .ELSEIF  wParam == IDCANCEL
       invoke	wsprintf, addr szInputText, addr szCancelPress
   	   mov dwInputLength, dwCancelPressLength  
       invoke EndDialog,hWnd,NULL
   .ENDIF
 .ENDIF
  xor    eax,eax
  ret
DialogProc endp
END  START
