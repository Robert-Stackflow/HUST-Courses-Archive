
/*
   用create function语句创建符合以下要求的函数：
   依据客户编号计算该客户所有储蓄卡的存款总额。
   函数名为：get_Records。函数的参数名可以自己命名:*/

CREATE OR REPLACE FUNCTION get_deposit(client_id integer)
 returns numeric(10,2)
 LANGUAGE plpgsql
AS
$$
begin
   return (select sum(b_balance) from bank_card where client_id=b_c_id and b_type='储蓄卡');
end;
$$;

/*  应用该函数查询存款总额在100万(含)以上的客户身份证号，姓名和存储总额(total_deposit)，
    结果依存款总额从高到代排序  */
select c_id_card,c_name,get_deposit(c_id) as total_deposit
from client
where get_deposit(c_id)>=1000000
order by total_deposit desc



/*  代码文件结束     */
/*  代码文件结束     */