.386
.MODEL FLAT, STDCALL
 MessageBoxA PROTO :DWORD,:DWORD, :DWORD,:DWORD
 ExitProcess     PROTO  :DWORD
; includelib  user32.lib
; includelib  kernel32.lib
MB_OK = 0
MB_OKCANCEL = 1 
MB_YESNOCANCEL = 3
.DATA
  szMsg  DB   "HOW ARE YOU!",0
  szTitle    DB   "Œ ∫Ú",0
.STACK 200
.CODE
 START:  
    invoke MessageBoxA, 0, offset szMsg, offset szTitle,MB_OKCANCEL
    invoke ExitProcess, 0
END START 