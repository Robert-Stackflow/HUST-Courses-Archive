-----请在以下空白处填写完成任务的语句，空白行可通过回车换行添加。
-----你也可以在命令行窗口完成任务，不过，在命令行键入的语句不会被保存。
create table dept
(
	deptNo INT primary key,
	deptName varchar(32)
);

create table staff
(
	staffNo INT primary key,
	staffName varchar(32),
	gender char(1),
	dob date,
	Salary numeric(8,2),
	deptNo INT,
	constraint FK_staff_deptNo foreign key(deptNo) references dept(deptNo)
);



------结束 