	  .686P
.model flat,c
 OPTION CASEMAP:NONE    ; 必须先申明 大小写敏感，否则对 windows.inc 处理会有错   
 include windows.inc 
 public MyExceptionProcess
  MessageBoxA PROTO STDCALL :DWORD,:DWORD, :DWORD,:DWORD
 sprintf  PROTO  :VARARG
 includelib      msvcrt.lib
.data
  szMsg  db   "exception occur at %08x, code: %08x, flag :%08x",0
  szTitle    DB   "异常已处理",0
  szContent  db  "运行正常了",0
  szNotOccur db  "该信息不会显示",0
;  DATAX  DD  10,20    ; 为BOUND 指令定义的数据
  lpOldHandle  dd  ?
 .code
end