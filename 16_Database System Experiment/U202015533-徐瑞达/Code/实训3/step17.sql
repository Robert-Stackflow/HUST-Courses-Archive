-- 17 查询2022年2月购买基金的高峰期。至少连续三个交易日，所有投资者购买基金的总金额超过100万(含)，则称这段连续交易日为投资者购买基金的高峰期。只有交易日才能购买基金,但不能保证每个交易日都有投资者购买基金。2022年春节假期之后的第1个交易日为2月7日,周六和周日是非交易日，其余均为交易日。请列出高峰时段的日期和当日基金的总购买金额，按日期顺序排序。总购买金额命名为amount。
--    请用一条SQL语句实现该查询：
-- select pro_purchase_time,amount from(
-- select pro_purchase_time,amount,count(*) over(partition by t1.minus) t1_minus from 
-- (
-- 	select pro_purchase_time,amount,(char_time-row_num) as minus from
-- 		(
-- 			select pro_purchase_time,sum(pro_quantity*f_amount) as amount,
-- 			row_number() over(order by pro_purchase_time) as row_num,
-- 			to_char(pro_purchase_time,'yyyyMMdd') as char_time from property,fund 
-- 			where pro_type=3 and pro_pif_id=f_id and 
-- 			pro_purchase_time < date '2022-03-01' and
-- 			pro_purchase_time >= date '2022-02-07' group by pro_purchase_time 
-- 			having sum(pro_quantity*f_amount) >= 1000000 order by pro_purchase_time
-- 		)
-- )t1
-- ) where t1_minus>=3;

with tb as(
select t1_time,t1_amount,t2_time,t2_amount,t3_time,t3_amount from
			(select pro_purchase_time,sum(pro_quantity*f_amount) as amount
			from property,fund where pro_type=3 and pro_pif_id=f_id and 
			pro_purchase_time < date '2022-03-01' and
			pro_purchase_time >= date '2022-02-07' group by pro_purchase_time 
			having sum(pro_quantity*f_amount) >= 1000000 order by pro_purchase_time)
			as t1(t1_time,t1_amount),
			(select pro_purchase_time,sum(pro_quantity*f_amount) as amount
			from property,fund where pro_type=3 and pro_pif_id=f_id and 
			pro_purchase_time < date '2022-03-01' and
			pro_purchase_time >= date '2022-02-07' group by pro_purchase_time 
			having sum(pro_quantity*f_amount) >= 1000000 order by pro_purchase_time)
			as t2(t2_time,t2_amount),
			(select pro_purchase_time,sum(pro_quantity*f_amount) as amount
			from property,fund where pro_type=3 and pro_pif_id=f_id and 
			pro_purchase_time < date '2022-03-01' and
			pro_purchase_time >= date '2022-02-07' group by pro_purchase_time 
			having sum(pro_quantity*f_amount) >= 1000000 order by pro_purchase_time)
			as t3(t3_time,t3_amount)
			where (t3_time=t2_time+1 and t2_time=t1_time+1) or
			(EXTRACT(dow FROM t1_time::TIMESTAMP)=5 and t3_time=t2_time+1 and t2_time=t1_time+3))
select t1_time as pro_purchase_time,t1_amount as amount from tb
union
select t2_time,t2_amount from tb
union
select t3_time,t3_amount from tb order by pro_purchase_time;

/*  end  of  your code  */