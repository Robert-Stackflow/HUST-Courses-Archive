.686P
.model flat,stdcall
ExitProcess proto  :dword
.code
start:
   mov al,1100101B
   mov ah, -1011101B
   add ah, al
   invoke ExitProcess, 0
end start