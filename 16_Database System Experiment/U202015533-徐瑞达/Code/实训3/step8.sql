-- 8) 查询持有两张(含）以上信用卡的用户的名称、身份证号、手机号。
--    请用一条SQL语句实现该查询：

select c_name,c_id_card,c_phone from client where c_id in (select b_c_id from bank_card where b_type='信用卡' group by b_c_id having count(b_c_id)>=2);




/*  end  of  your code  */