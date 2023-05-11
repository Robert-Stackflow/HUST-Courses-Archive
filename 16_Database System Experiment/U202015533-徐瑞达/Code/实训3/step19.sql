-- 19) 以日历表格式列出2022年2月每周每日基金购买总金额，输出格式如下：
-- week_of_trading Monday Tuesday Wednesday Thursday Friday
--               1
--               2    
--               3
--               4
--   请用一条SQL语句实现该查询：
select week_of_trading,
SUM(case day_of_week when 1 then amount else null end) as monday,
SUM(case day_of_week when 2 then amount else null end) as tuesday,
SUM(case day_of_week when 3 then amount else null end) as wendnesday,
SUM(case day_of_week when 4 then amount else null end) as thursday,
SUM(case day_of_week when 5 then amount else null end) as friday from
(
select date_part('week',pro_purchase_time)-5 as week_of_trading,EXTRACT(dow FROM pro_purchase_time::TIMESTAMP) as day_of_week,sum(pro_quantity*f_amount) as amount
from property,fund where pro_purchase_time < date '2022-03-01' and
pro_purchase_time >= date '2022-02-07' and pro_type=3 and pro_pif_id = f_id group by pro_purchase_time,week_of_trading order by week_of_trading)
group by week_of_trading;





/*  end  of  your code  */