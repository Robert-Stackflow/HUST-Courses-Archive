.686P
.model flat, c
  ExitProcess proto stdcall :dword
  scanf       proto :ptr sbyte, :VARARG
;  includelib  msvcrt.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
course   struct
cid      dd  ?          ;�γ̱��
align 1
ctitle   db  20 dup(0)  ;�γ���
chour    db  0          ;ѧʱ��
cteacher db 10 dup(0)   ;������ʦ
cterm    db  1          ;����ѧ��
course  ends
.data
lpfmt db '%s',0
Ke1   course <>
Ke2   course <2102,'math',40,'liming',2>
      course <2103,'chinese',80,'zhangsan',>
ke3   course 5 dup(<2104, , 60, ,>)
      course 10 dup(<>)
.stack 200
.code
main proc  
    mov    ke1.cid, 100
	    invoke scanf, offset lpfmt, offset ke1.ctitle
	    lea    ebx, ke1
	    mov    [ebx].course.chour, 40
	    mov    [ebx].course.cterm, 2
    invoke  ExitProcess, 0
main endp
end 
