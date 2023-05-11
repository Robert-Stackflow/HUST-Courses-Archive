-- 创建存储过程`sp_fibonacci(in m int)`，向表fibonacci插入斐波拉契数列的前m项，及其对应的斐波拉契数。fibonacci表初始值为一张空表。请保证你的存储过程可以多次运行而不出错。

create procedure sp_fibonacci(in m int)
as
	declare n1 bigint default 0;
	declare n2 bigint default 1;
	declare n3 bigint default 1;
	declare i int default 3;
begin

	if not exists (select * from fibonacci where n=0)then
	insert into fibonacci values(0,n1);
	end if;

	if m = 1 then
	return;
	end if;

	if not exists (select * from fibonacci where n=1)then 
	insert into fibonacci values(1,n2);
	end if;

	if m = 2 then
	return;
	end if;

	if not exists (select * from fibonacci where n=2) then
	insert into fibonacci values(2,n3);
	end if;

	while i<m loop
			insert into fibonacci values(i,(select fibn from fibonacci where n=i-1)+(select fibn from fibonacci where n=i-2));
		i := i+1;
	end loop;
end;