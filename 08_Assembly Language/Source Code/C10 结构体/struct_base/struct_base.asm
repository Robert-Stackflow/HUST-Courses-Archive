

course   struct
cid        dd  0          ; 课程编号
ctitle     db  20 dup(0)  ; 课程名
chour      db  0          ; 学时数
cteacher   db  10 dup(0)  ; 主讲教师
cterm      db  1          ; 开课学期
course  ends

department  struct
   dname     db  10  dup(0)  ; 系名
   daddress    db  10  dup(0)  ; 系的办公地址
   coursetable  course  <>    ; 课表，无初始信息
department  ends
; <123,'xuxiang',0,'xu',1 > 

.686P
.model flat,c

ExitProcess PROTO STDCALL :DWORD
  includelib  kernel32.lib
 ; includelib      msvcrt.lib
 includelib  libcmt.lib
 includelib  legacy_stdio_definitions.lib
  printf          PROTO C :ptr sbyte, :VARARG
  scanf          PROTO C :ptr sbyte, :VARARG
.data
lpfmt  db '%s',0
x      db  100 dup(0)
y   department <>
ke1  course <>
ke2  course <2102,'math',40,'liming',2> 
     course  <2103,'chinese',80,'zhangsan',> 
; cterm字段未重新赋值，默认为1
ke3  course  5 dup(<2104, , 60, ,>)
     ; 定义了5个相同的结构变量，对cid、chour赋了值
course  10 dup(<>) 

.code
; start:  
main proc
 mov  eax, ke2.cid       ; 将2102送到eax寄存器中
mov  al, ke2.ctitle    ; ctitle中的字符‘m’送到al中
mov  ah, ke2.ctitle+2  ; ctitle中的字符‘t’送到ah中

mov  ebx, offset  ke2
mov  al, [ebx].course.chour
mov  al, (course ptr [ebx]).chour

mov  ecx,  type  ke1     ; (ecx)=24H
mov  ecx,  type  ke3     ; (ecx)=24H


 	 mov  (course ptr X).cid, 100
invoke SCANF, offset lpfmt,offset (course ptr X).ctitle
lea    ebx, X
mov    [ebx].course.chour, 40
lea    esi, [ebx + offset course.cteacher]
invoke SCANF, offset lpfmt, esi, 10
mov   ( course ptr [ebx]).cterm, 2
    invoke ExitProcess, 0
	main endp
	end
;end start
