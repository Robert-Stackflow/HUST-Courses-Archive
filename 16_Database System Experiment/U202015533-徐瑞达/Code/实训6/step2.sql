
-- 编写一存储过程，自动安排某个连续期间的大夜班的值班表:

create procedure sp_night_shift_arrange(in start_date date, in end_date date)
AS
	declare cur_date date;
	declare cur_week integer;
	declare is_checked boolean;
	declare times integer :=0;
	declare doctor char(30);
	declare manager char(30);
	declare nurse1 char(30);
	declare nurse2 char(30);
	CURSOR cursor_doctor FOR
	select e_name from employee where e_type=1 or e_type=2;
	CURSOR cursor_nurse FOR
	select e_name from employee where e_type=3;
begin
	cur_date := start_date;
	select e_name into manager from employee where e_type=1;
	OPEN cursor_doctor;
	OPEN cursor_nurse;
	while cur_date <= end_date loop
		cur_week := EXTRACT(dow FROM cur_date::TIMESTAMP);
		fetch cursor_nurse into nurse1;
		if cursor_nurse% NOTFOUND then
			close cursor_nurse;
			open cursor_nurse;
			fetch cursor_nurse into nurse1;
		end if;
		fetch cursor_nurse into nurse2;
		if cursor_nurse% NOTFOUND then
			close cursor_nurse;
			open cursor_nurse;
			fetch cursor_nurse into nurse2;
		end if;
		if cur_week=1 and is_checked=true then
			doctor := manager;
			is_checked := false;
		elseif cur_week=0 or cur_week=6 then
			fetch cursor_doctor into doctor;
			if cursor_doctor % NOTFOUND then
				close cursor_doctor;
				open cursor_doctor;
				fetch cursor_doctor into doctor;
			end if;
			if doctor=manager then
				is_checked := true;
				fetch cursor_doctor into doctor;
				if cursor_doctor % NOTFOUND then
					close cursor_doctor;
					open cursor_doctor;
					fetch cursor_doctor into doctor;
				end if;
			end if;
		else
			fetch cursor_doctor into doctor;
			if cursor_doctor% NOTFOUND then
				close cursor_doctor;
				open cursor_doctor;
				fetch cursor_doctor into doctor;
			end if;
		end if;
		insert into night_shift_schedule values(cur_date,doctor,nurse1,nurse2);
		cur_date := cur_date::date + interval '1 D';
	end loop;
end;

/*  end  of  your code  */ 
