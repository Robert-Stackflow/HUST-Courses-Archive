

course   struct
cid        dd  0          ; �γ̱��
ctitle     db  20 dup(0)  ; �γ���
chour      db  0          ; ѧʱ��
cteacher   db  10 dup(0)  ; ������ʦ
cterm      db  1          ; ����ѧ��
course  ends

department  struct
   dname     db  10  dup(0)  ; ϵ��
   daddress    db  10  dup(0)  ; ϵ�İ칫��ַ
   coursetable  course  <>    ; �α��޳�ʼ��Ϣ
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
; cterm�ֶ�δ���¸�ֵ��Ĭ��Ϊ1
ke3  course  5 dup(<2104, , 60, ,>)
     ; ������5����ͬ�Ľṹ��������cid��chour����ֵ
course  10 dup(<>) 

.code
; start:  
main proc
 mov  eax, ke2.cid       ; ��2102�͵�eax�Ĵ�����
mov  al, ke2.ctitle    ; ctitle�е��ַ���m���͵�al��
mov  ah, ke2.ctitle+2  ; ctitle�е��ַ���t���͵�ah��

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
