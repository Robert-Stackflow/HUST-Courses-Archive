	  .686P
.model flat,c
 OPTION CASEMAP:NONE    ; ���������� ��Сд���У������ windows.inc ������д�   
 include windows.inc 
 public MyExceptionProcess
  MessageBoxA PROTO STDCALL :DWORD,:DWORD, :DWORD,:DWORD
 sprintf  PROTO  :VARARG
 includelib      msvcrt.lib
.data
  szMsg  db   "exception occur at %08x, code: %08x, flag :%08x",0
  szTitle    DB   "�쳣�Ѵ���",0
  szContent  db  "����������",0
  szNotOccur db  "����Ϣ������ʾ",0
;  DATAX  DD  10,20    ; ΪBOUND ָ��������
  lpOldHandle  dd  ?
 .code
end