
-- 在金融应用场景数据库中，编程实现一个转账操作的存储过程sp_transfer_balance，实现从一个帐户向另一个帐户转账。
-- 请补充代码完成该过程：
create procedure sp_transfer(IN applicant_id int,      
                     IN source_card_id char(30),
					 IN receiver_id int, 
                     IN dest_card_id char(30),
					 IN	amount numeric(10,2),
					 OUT return_code int)
as 
	declare source_type char(20);
	declare dest_type char(20);
	declare source_balance numeric(10,2);
	declare dest_balance numeric(10,2);
begin	
	if not exists (select * from bank_card where applicant_id=b_c_id and source_card_id= b_number) then
	return 0;
	end if;
	if not exists (select * from bank_card where receiver_id=b_c_id and dest_card_id= b_number) then
	return 0;
	end if;
	select b_balance into source_balance from bank_card where source_card_id= b_number;
	select b_balance into dest_balance from bank_card where dest_card_id= b_number;
	select b_type into source_type from bank_card where source_card_id= b_number;
	select b_type into dest_type from bank_card where dest_card_id= b_number;
	if source_type='信用卡' and dest_type='储蓄卡' then
	return 0;
	end if;
	if source_balance < amount then
	return 0;
	end if;
	update bank_card set b_balance=source_balance-amount where source_card_id= b_number;
	if dest_type='储蓄卡' then
	update bank_card set b_balance=dest_balance+amount where dest_card_id= b_number;
	else
	update bank_card set b_balance=dest_balance-amount where dest_card_id= b_number;
	end if;
	commit;
	return 1;
end; 

/*  end  of  your code  */ 








/*  end  of  your code  */ 