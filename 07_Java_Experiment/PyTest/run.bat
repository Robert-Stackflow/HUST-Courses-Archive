@echo off
python ./main.py
:loop
set /p a= [Question] Whether to open the log directory(Y/N)
if /i '%a%'=='Y' goto continue
if /i '%a%'=='N' goto end
goto loop
:continue
start "" "D:\HUST-Courses\07_Java_Experiment\PyTestDIR\logs"
:end
@exit