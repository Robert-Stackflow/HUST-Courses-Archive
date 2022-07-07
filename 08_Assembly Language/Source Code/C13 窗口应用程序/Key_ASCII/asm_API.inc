; *****************
; user32 ÖÐµÄº¯Êý
; *****************
UpdateWindow PROTO :DWORD
ShowWindow   PROTO :DWORD,:DWORD

DispatchMessageA PROTO :DWORD
DispatchMessage equ <DispatchMessageA>

GetMessageA PROTO :DWORD,:DWORD,:DWORD,:DWORD
GetMessage equ <GetMessageA>

TranslateMessage PROTO :DWORD

GetDC PROTO :DWORD
RegisterClassExA PROTO :DWORD
RegisterClassEx equ <RegisterClassExA>

PostQuitMessage PROTO :DWORD

LoadIconA PROTO :DWORD,:DWORD
LoadIcon equ <LoadIconA>

LoadCursorA PROTO :DWORD,:DWORD
LoadCursor equ <LoadCursorA>

CreateWindowExA PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD,:DWORD
CreateWindowEx equ <CreateWindowExA>

DefWindowProcA PROTO :DWORD,:DWORD,:DWORD,:DWORD
DefWindowProc equ <DefWindowProcA>

; *******************
; kernel32
; *******************
GetModuleHandleA PROTO :DWORD
GetModuleHandle equ <GetModuleHandleA>

GetCommandLineA PROTO 
GetCommandLine equ <GetCommandLineA>

ExitProcess PROTO :DWORD

RtlZeroMemory PROTO :DWORD,:DWORD

; *******************
; gdi32
; *******************
TextOutA PROTO :DWORD,:DWORD,:DWORD,:DWORD,:DWORD
TextOut equ <TextOutA>